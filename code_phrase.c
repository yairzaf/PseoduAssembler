
#include "code_phrase.h"
#include "bits.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



void phrase_files(char *argv[])
{


    char file_flag=1;
    int file_counter=0;
    while(file_flag)
    {

        next_file(argv);file_counter++;
        file_flag=strcmp(file_name,"END");
        if(file_flag)
        {
            printf("\ncompiling - %s\n",file_name);
            process_file();

        }
    }
    if(file_counter==1)
        printf("error: expected files.\n");
    compiler_end();

}

void process_file()
{

    compiler_reset();

    reset_error_report();

    if(open_file())
    {

        read_file();

        close_file();
    }
    else
    {

        report_error(1,0);
    }

    compile();
    summary_report();

}

void read_file()
{

    stage_1();
}

void stage_1()
{
    int i;
    char eof_flag=1;
    line_counter=0;
    do
    {

        get_next_line();line_counter++;
        if((eof_flag=strcmp(line,"EOF")))
            phrase_line_1();
    }
    while(eof_flag);
    if(line_counter==1)
        report_error(2,0);
    else
    {
        for(i=0;i<ext_counter;i++)
            add_label(externs[i]);
        reset_read();
        stage_2();
    }

}
void stage_2()
{
    char eof_flag=1;
    line_counter=0;
    do
    {

        get_next_line();line_counter++;
        if((eof_flag=strcmp(line,"EOF")))
            phrase_line_2();
    }
    while(eof_flag);
}
void phrase_line_1()
{
    int num;
    line_index=0;
    if(!empty_line())
    {
        num=dissect_command();
        find_label();
        find_extern(num);
        find_num(num);
    }
}
void phrase_line_2()
{
    line_index=0;
    int i;


    if(!empty_line())
    {

        for(i=0;i<5;i++)
        command[i]=-1;
        command[5]=line_counter;
        process_arguments(process_command(dissect_command()));
        add_command(command);
    }
}
void find_label()
{

    int flag=1,i,len=strlen(dissected[0]);
    if(dissected[0][len-1]==':')
    {
        if(len>=LABEL_SIZE)
        {
            report_error(4,line_counter);
            return;
        }
        if((dissected[0][0]>='a' && dissected[0][0]<='z') || (dissected[0][0]>='A' && dissected[0][0]<='Z'))
        {
            i=1;
            while(flag)
            {
                if(!((dissected[0][i]>='a' && dissected[0][i]<='z')||(dissected[0][i]>='A' && dissected[0][i]<='Z') || (dissected[0][i]>='0' && dissected[0][i]<='9')))
                    flag=0;
                else
                    i++;
            }
            if(dissected[0][i]==':')
            {
                dissected[0][i]='\0';
                if(!(get_ext(dissected[0])!=-1 || get_label(dissected[0])!=-1 || get_reg(dissected[0])!=-1 || get_op(dissected[0])!=-1 || get_spec(dissected[0])!=-1))
                {
                    add_label(dissected[0]);
                }
                else
                    report_error(5,line_counter);
            }
            else
                report_error(13,line_counter);
        }
        else
            report_error(13,line_counter);

    }
}
void find_extern(int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        if(dissected[i][0]=='.')
        {

            if(get_spec(&dissected[i][1])==3)
            {

                if(i<n)
                {
                    i++;
                    if((dissected[i][0]>='a'&&dissected[i][0]<='z') || (dissected[i][0]>='A'&&dissected[i][0]<='Z'))
                    {

                        for(j=1;j<strlen(dissected[i]);j++)
                        {
                            if(!((dissected[i][j]>='a' && dissected[i][j]<='z') || (dissected[i][j]>='A'&&dissected[i][j]<='Z') || (dissected[i][j]>='0'&&dissected[i][j]<='9')))
                            {
                                return;
                            }

                        }
                        if(!(get_ext(dissected[i])!=-1 || get_label(dissected[i])!=-1 || get_reg(dissected[i])!=-1 || get_op(dissected[i])!=-1 || get_spec(dissected[i])!=-1))
                        {
                            add_ext(dissected[i]);
                        }
                        else
                            report_error(5,line_counter);

                        return;
                    }
                }
            }
        }
    }
}
void find_num(int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(dissected[i][0]=='#')
        {
            if((dissected[i][1]>='0' && dissected[i][1]<='9') || ((dissected[i][1]=='+' || dissected[i][1]=='-') && (dissected[i][2]>='0' && dissected[i][2]<='9')))
            {
                add_num(&dissected[i][1]);
            }
            else
                report_error(6,line_counter);
        }
    }
}
int empty_line()
{
    SKIP_WHITE_SPACE(line_index);
    if(line[line_index]==';' || line[line_index]=='\0' || line[line_index]=='\n')
    {
        return 1;
    }
    return 0;
}
int end_of_line()
{
    SKIP_WHITE_SPACE(line_index);
    if(line[line_index]=='\0' || line[line_index]=='\n')
    {
        return 1;
    }

    return 0;
}

int dissect_command()
{
    int i,j,len;
    char *part;
    const char w[2]=" ";
    line_index=0;
    for(i=0;i<strlen(line);i++)
    {
        if(line[i]=='"')
        {
            i++;
            while(line[i]!='"' && i<strlen(line))
            {
               i++;
               if(line[i]==' ')
                    line[i]='\n';
            }

        }
        if(line[i]=='\t')
            line[i]=' ';
    }
    for(i=0;i<strlen(line);i++)
    {

        j=0;
        while(line[i+j]==' ')
        {
            j++;
        }
        if(line[i]==' ' && j>1)
        {
            strcpy(&line[i+1],&line[i+j]);
        }
    }
    if(line[0]==' ')
        strcpy(&line[0],&line[1]);
    for(i=0;i<strlen(line);i++)
    {
        if(line[i]=='"')
        {
            i++;
            while(line[i]!='"'&&i<strlen(line))
                i++;
        }
        if((line[i]==':' || line[i]=='(' || line[i]==',' || line[i]==')') && (line[i+1]!=' '))
        {
            for(j=strlen(line);j>i;j--)
                line[j+1]=line[j];
            line[i+1]=' ';
        }
        if((line[i]=='(' || line[i]==',' || line[i]==')') && (line[i-1]!=' '))
        {
            for(j=strlen(line);j>i-1;j--)
                line[j+1]=line[j];
            line[i]=' ';
        }

    }
    if(line[strlen(line)-1]=='\n')
        line[strlen(line)-1]='\0';

    len=0;
    dissected=malloc(len * sizeof(char *));
    part = strtok(line,w);

    while(part!=NULL)
    {

        len++;
        dissected=realloc(dissected,len * sizeof(char *));
        dissected[len-1]=(char *)malloc(sizeof(char)*LINE_SIZE);
        strcpy(dissected[len-1],part);
        part = strtok(NULL,w);
    }
    return len;
}

int process_command(int num)
{
    int label=-1,op=-1,state;

    if(dissected[0][strlen(dissected[0])-1]==':')
    {
        dissected[0][strlen(dissected[0])-1]='\0';
        label=get_label(dissected[0]);
        if(label==-1)
        {
            report_error(13,line_counter);
        }

        state=1;
    }
    else
        state=0;
    if((state==1&&num>1) || state==0)
    {
        if(dissected[state][0]=='.')
        {
            op=get_spec(&dissected[state][1]);
            if(op!=-1)
                op+=20;
        }
        else
            op=get_op(dissected[state]);
        if(op==-1)
            report_error(8,line_counter);

    }

    command[0]=label;
    command[1]=op;
    return num;
}
int get_arg(char *a)
{
    int ret=-1;
    if(a[0]=='#')
        ret=get_num(&a[1]);

    if(ret==-1)
        ret=get_label(a);

    if(ret==-1)
        ret=get_reg(a);


    return ret;
}
int get_string(int position)
{
    int i,len,ret,flag=1;
    int p[1];
    len=strlen(dissected[position]);
    ret=data_pointer;
    for(i=0;i<len;i++)
    {
        if(dissected[position][i]=='\n')
            dissected[position][i]=' ';
    }
    i=0;
    if((dissected[position][0]=='"' && dissected[position][len-1]=='"') && (len>2))
    {
       i++;
       while(flag)
       {
            if(dissected[position][i]!='"')
            {
                p[0]=(int)dissected[position][i];
                add_data(p);
                i++;
            }
            else
                flag=0;
       }
       p[0]=0;
       add_data(p);
       return ret;
    }
    else
    {
        report_error(14,line_counter);
        return -1;
    }
}
int get_data(int position,int num)
{
    int i,flag=1,ret,len;
    int r[1];
    ret=data_pointer;

    while(flag)
    {
        len=strlen(dissected[position]);
        i=0;
        if((dissected[position][0]>='0' && dissected[position][0]<='9') || ((dissected[position][0]=='+'||dissected[position][0]=='-') && (dissected[position][1]>='0'&&dissected[position][1]<='9')))
        {
            i++;
            while((dissected[position][i]>='0' && dissected[position][i]<='9'))i++;
            if(i==len)
            {
                r[0]=atoi(dissected[position]);
                add_data(r);
            }
            else
            {
                report_error(6,line_counter);
                flag=0;
            }

        }
        if(position<num-1)
        {
            position++;
            if(dissected[position][0]==',' && strlen(dissected[position])==1)
            {
                if(position<num-1)
                    position++;
                else
                {
                    report_error(9,line_counter);
                    flag=0;
                }
            }
            else
                report_error(12,line_counter);
        }
        else
            flag=0;
    }
    return ret;
}
void process_arguments(int num)
{
    int label=-1,arg1=-1,arg2=-1,current;
    if(command[0]==-1)
        current=0;
    else
        current=1;
    if(command[1]!=-1)
    {

        if((0<=command[1]&&3>=command[1]) || command[1]==6)
        {
            if(current<num-1)
            {
                current++;
                arg1=get_arg(dissected[current]);
                if(current<num-1)
                {
                    current++;
                    if(dissected[current][0]==',' && strlen(dissected[current])==1)
                    {
                        if(current<num-1)
                        {
                            current++;
                            arg2=get_arg(dissected[current]);
                            if(arg1==-1||arg2==-1)
                                report_error(11,line_counter);
                            if(current<num-1)
                                report_error(10,line_counter);
                        }
                        else
                            report_error(9,line_counter);

                    }
                    else
                        report_error(12,line_counter);

                }
                else
                report_error(9,line_counter);
            }
            else
                report_error(9,line_counter);
        }
        if((4<=command[1] && 8>=command[1] && command[1]!=6) || command[1]==11 || command[1]==12)
        {
            if(current<num-1)
            {
                current++;
                arg1=get_arg(dissected[current]);
                if(current<num-1)
                    report_error(10,line_counter);
                else if(arg1==-1)
                    report_error(11,line_counter);
            }
            else
                report_error(9,line_counter);
        }
        if(command[1]==9 || command[1]==10 || command[1]==13)
        {
            if(current<num-1)
            {
                current++;
                label=get_arg(dissected[current]);
                if(label==-1)
                    report_error(11,line_counter);
                if(current<num-1)
                {
                    current++;
                    if(dissected[current][0]=='(' && strlen(dissected[current])==1)
                    {
                        if(current<num-1)
                        {
                            current++;
                            arg1=get_arg(dissected[current]);
                            if(arg1==-1)
                                report_error(11,line_counter);
                            if(current<num-1)
                            {
                                current++;
                                if(dissected[current][0]==',' && strlen(dissected[current])==1)
                                {
                                    if(current<num-1)
                                    {
                                        current++;
                                        arg2=get_arg(dissected[current]);
                                        if(arg2==-1)
                                            report_error(11,line_counter);
                                        if(current<num-1)
                                        {
                                            current++;
                                            if(dissected[current][0]==')' && strlen(dissected[current])==1)
                                            {
                                                if(current<num-1)
                                                    report_error(10,line_counter);
                                            }
                                            else
                                                report_error(12,line_counter);
                                        }
                                        else
                                            report_error(12,line_counter);
                                    }
                                    else
                                        report_error(9,line_counter);
                                }
                                else
                                    report_error(12,line_counter);
                            }
                            else
                                report_error(9,line_counter);
                        }
                        else
                            report_error(9,line_counter);
                    }
                    else
                        report_error(11,line_counter);
                }
            }
            else
                report_error(9,line_counter);
        }
        if(14==command[1] || 15==command[1])
        {
            if(current<num-1)
                report_error(10,line_counter);
        }
        if(command[1]==20)
        {
            if(current<num-1)
            {
                current++;
                label=get_data(current,num);
            }
            else
                report_error(9,line_counter);
        }
        if(command[1]==21)
        {
            if(current<num-1)
            {
                current++;
                if(current<num-1)
                    report_error(10,line_counter);
                else
                    label=get_string(current);
            }
            else
                report_error(9,line_counter);
        }
        if(command[1]==22 || command[1]==23)
        {
            if(current<num-1)
            {
                current++;
                label=get_arg(dissected[current]);
                if(!(label>=10))
                {
                    report_error(11,line_counter);
                }
                if(current<num-1)
                {
                    report_error(10,line_counter);
                }
            }
            else
                report_error(9,line_counter);
        }


    }
    command[2]=label;
    command[3]=arg1;
    command[4]=arg2;

}
