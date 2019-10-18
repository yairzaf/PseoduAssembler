#include "bits.h"
#include "compiler.h"
#include "error_report.h"
#include "file_handle.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void binary_reset()
{
    ic=0;
    dc=0;
    exc=0;
    enc=0;
    address_counter=0;
    instruction_segment=malloc(ic*sizeof(char *));
    data_segment=malloc(dc*sizeof(char *));
    externals=malloc(exc*sizeof(char *));
    enteries=malloc(enc*sizeof(char *));
    label_adress=malloc((address_counter)*sizeof(int *));
}
void binary_end()
{

    free(instruction_segment);
    free(data_segment);
    free(enteries);
    free(externals);
    free(label_adress);

}
void add_address(int adr)
{

    address_counter++;
    label_adress=realloc(label_adress,address_counter * sizeof(int *));
    label_adress[address_counter-1]=(int *)malloc(sizeof(int *)*1);
    label_adress[address_counter-1][0]=adr;
}
void add_externals(char *ext)
{
    exc++;
    externals=realloc(externals,exc*sizeof(char*));
    externals[exc-1]=(char *)malloc(sizeof(char)*LINE_SIZE);
    strcpy(externals[exc-1],ext);

}
void add_enteries(char *ent)
{
    enc++;
    enteries=realloc(enteries,enc*sizeof(char*));
    enteries[enc-1]=(char *)malloc(sizeof(char)*LINE_SIZE);
    strcpy(enteries[enc-1],ent);
}
void add_instructions(char *ins)
{
    ic++;
    instruction_segment=realloc(instruction_segment,ic*sizeof(char*));
    instruction_segment[ic-1]=(char *)malloc(sizeof(char)*WORD_SIZE);
    strcpy(instruction_segment[ic-1],ins);
}
void add_data_seg(char *dat)
{
    dc++;
    data_segment=realloc(data_segment,dc*sizeof(char*));
    data_segment[dc-1]=(char *)malloc(sizeof(char)*WORD_SIZE);
    strcpy(data_segment[dc-1],dat);
}


void errors_check()
{

    int i,j,tmp;

    for(i=0;i<program_pointer;i++)
    {
        if(program[i][1]==0 || program[i][1]==2 || program[i][1]==3)
        {
            if(arg_type(program[i][4])==0)
                report_error(16,program[i][5]);
        }
        if(program[i][1]==4 || program[i][1]==5 || program[i][1]==7 || program[i][1]==8 || program[i][1]==11)
        {
            if(arg_type(program[i][3])==0)
                report_error(17,program[i][5]);
        }
        if(program[i][1]==6)
        {
            if(arg_type(program[i][3])!=1)
                report_error(17,program[i][5]);
            if(arg_type(program[i][4])==0)
                report_error(16,program[i][5]);
        }
        if(program[i][1]==9 || program[i][1]==10 || program[i][1]==13)
        {
            if(arg_type(program[i][2])==0)
                report_error(17,program[i][5]);
        }
         if((program[i][1]==22 || program[i][1]==23) && program[i][0]!=-1)
         {
             report_warning(2,program[i][5]);
             tmp=program[i][0];
             //program[i][0]=-1;
             for(j=0;j<program_pointer;j++)
             {
                 if(program[j][2]==tmp || program[j][3]==tmp || program[j][4]==tmp)
                    report_error(15,program[j][5]);
             }
         }
         if((program[i][1]==22) && program[i][2]!=-1 && i<program_pointer)
         {

             tmp=program[i][2];
             //program[i][0]=-1;
             for(j=i+1;j<program_pointer;j++)
             {
                 if(program[j][1]==22 && program[j][2]==tmp)
                    report_error(5,program[j][5]);
             }
         }
    }
}

void create_binary(int n)
{
    int i;
    for(i=0;i<WORD_SIZE;i++)
    {
        if(n>>i&1)
            binary[(WORD_SIZE-1)-i]='/';
        else
            binary[(WORD_SIZE-1)-i]='.';
    }
}

int over_flow(int n)
{
    int tmp=n;
    if(tmp<0)
        tmp=~n;
    if(tmp>16383)
        return 1;
    return 0;
}
void create_data()
{
    int i,*tmp;
    for(i=0;i<data_pointer;i++)
    {
        tmp=&data[i][0];
        create_binary(tmp[0]);
        add_data_seg(binary);

    }
}
int arg_type(int arg)
{
    int ret=-1;
    if(arg>=0&&arg<=7)
        ret=3;
    if(arg>=10)
        ret=1;
    if(arg<=-10)
        ret=0;
    return ret;
}
int create_arg(int arg,int point)
{
    int type=arg_type(arg),i,ret=-1;
    if(type==3)
    {
        ret=arg;
    }
    if(type==1)
    {
        ret=arg-10;
    }
    if(type==0)
    {
        i=(arg*-1)-10;
        ret=atoi(numbers[i]);
        if(over_flow(ret<<2))
            report_warning(1,program[i][5]);
    }
    return ret;
}
void create_instructions()
{

    int i,operation,arg1,arg2,tmp;
    for(i=0;i<program_pointer;i++)
    {

        if(program[i][0]!=-1)
        {
            if(program[i][1]==21 || program[i][1]==20)
            {
                tmp=(program[i][2]*-1)-10;
                add_address(tmp);


            }
            else if(program[i][1]==22 || program[i][1]==23)
            {

                add_address(-1);

            }
            else
            {
                add_address(ic) ;

            }

        }
        if(program[i][1]>=0&&program[i][1]<=15)
        {
            operation = program[i][1];

            operation<<=6;
            if((0<=program[i][1] && 3>=program[i][1]) || program[i][1]==6)
            {
                if(program[i][3]!=-1 && program[i][4]!=-1)
                {
                    tmp=arg_type(program[i][3]);
                    tmp<<=4;
                    operation|=tmp;
                    tmp=arg_type(program[i][4]);
                    tmp<<=2;
                    operation|=tmp;


                }
            }
            if((4<=program[i][1]&&8>=program[i][1]&&program[i][1]!=6) || program[i][1]==11 || program[i][1]==12)
            {
                if(program[i][3]!=-1)
                {
                    tmp=arg_type(program[i][3]);
                    tmp<<=2;
                    operation|=tmp;


                }
            }
            if(program[i][1]==9 || program[i][1]==10 || program[i][1]==13)
            {

                if(program[i][2]!=-1 && program[i][3]!=-1 && program[i][4]!=-1)
                {
                    tmp=2;
                    tmp<<=2;
                    operation|=tmp;
                    tmp=arg_type(program[i][3]);
                    tmp<<=12;
                    operation|=tmp;
                    tmp=arg_type(program[i][4]);
                    tmp<<=10;
                    operation|=tmp;



                }
                else if(program[i][2]!=-1)
                {
                    tmp=arg_type(program[i][2]);
                    tmp<<=4;
                    operation|=tmp;


                }

            }
            if(14==program[i][1] || 15==program[i][1])
            {

            }
            create_binary(operation);
            add_instructions(binary);

            if(program[i][2]!=-1)
            {
                tmp=create_arg(program[i][2],program[i][5]);
                if(arg_type(program[i][2])==1)
                {

                    itoa(tmp,binary,10);
                }
                else
                {

                    tmp<<=2;
                    create_binary(tmp);
                }
                add_instructions(binary);
            }
            if(arg_type(program[i][3])==3 && arg_type(program[i][4])==3)
            {
                arg1=create_arg(program[i][3],program[i][5]);
                arg2=create_arg(program[i][4],program[i][5]);
                arg1<<=8;
                arg2<<=2;
                arg1|=arg2;
                create_binary(arg1);
                add_instructions(binary);
            }
            else
            {
                if(arg_type(program[i][3])!=-1)
                {
                    if(arg_type(program[i][3])==1)
                    {
                        tmp=create_arg(program[i][3],program[i][5]);
                        itoa(tmp,binary,10);
                    }
                    else
                    {
                        tmp=create_arg(program[i][3],program[i][5])<<2;
                        if(arg_type(program[i][3])==3)
                            tmp<<=6;
                        create_binary(tmp);
                    }

                    add_instructions(binary);
                }
                if(arg_type(program[i][4])!=-1)
                {
                    if(arg_type(program[i][4])==1)
                        itoa(create_arg(program[i][4],program[i][5]),binary,10);
                    else
                        create_binary(create_arg(program[i][4],program[i][5])<<2);
                    add_instructions(binary);
                }
            }

        }

    }



}

void create_enteris()
{
    int i,l,label,adress;
    char entery[LINE_SIZE];
    for(i=0;i<program_pointer;i++)
    {
        if(program[i][1]==22 && program[i][2]!=-1)
        {
            label = program[i][2];
            l=label-10;
            adress=label_adress[l][0];
            if(adress<=-10)
                adress=(adress*(-1)-10)+(ic);
            adress+=OFFSET;
            strcpy(entery,labels[l]);
            strcat(entery,"\t");
            itoa(adress,&entery[strlen(labels[l])+1],10);
            add_enteries(entery);
        }
    }
}
void create_labels()
{
    int i,j,adress;
    char exter[LINE_SIZE];
    for(i=0;i<ic;i++)
    {
        if(instruction_segment[i][0]!='.'&&instruction_segment[i][0]!='/')
        {
            j=atoi(instruction_segment[i]);

            if(j>=label_counter-ext_counter)
            {
                strcpy(exter,labels[j]);
                strcat(exter,"\t");
                itoa(i+OFFSET,&exter[strlen(labels[j])+1],10);
                add_externals(exter);
                adress=1;
            }
            else
            {
                adress=label_adress[j][0];
                if(adress<=-10)
                    adress=(adress*(-1)-10)+(ic);
                adress+=OFFSET;
                adress<<=2;
                adress|=2;

            }
            /*itoa(adress,binary,10);
            strcat(binary,labels[j]);*/

            create_binary(adress);
            strcpy(instruction_segment[i],binary);

        }
    }
}
void output()
{
    int i,j;

    printf("\n\ninstruction segment:\n-------------\n\n");
    for(i=0;i<ic;i++)
        printf("%d: %s\n",i+OFFSET,instruction_segment[i]);
    printf("\n\ndata segment:\n-------------\n\n");
    for(j=0;j<dc;j++)
        printf("%d: %s\n",OFFSET+i+j,data_segment[j]);
    printf("\n\nlabel addresses:\n-------------\n\n");
    for(j=0;j<address_counter;j++)
        printf("%d: %d\n",j,label_adress[j][0]);
    printf("\n\nENTERIES:\n-------------\n\n");
    for(j=0;j<enc;j++)
        printf("%s\n",enteries[j]);
    printf("\n\nEXTERNALS:\n-------------\n\n");
    for(j=0;j<exc;j++)
        printf("%s\n",externals[j]);
}
void output_files()
{
    int i,j;
    char tmp[LINE_SIZE];

    if(ic || dc)
    {

        create_file(".ob");
        itoa(ic,tmp,10);
        strcat(tmp,"\t");
        itoa(dc,&tmp[strlen(tmp)],10);
        strcat(tmp,"\n");
        write_next_line(tmp);
        for(i=0;i<ic;i++)
        {
            itoa(i+OFFSET,tmp,10);
            strcat(tmp,"\t");
            strcat(tmp,instruction_segment[i]);
            strcat(tmp,"\n");
            write_next_line(tmp);

        }
        for(j=0;j<dc;j++)
        {
            itoa(i+j+OFFSET,tmp,10);
            strcat(tmp,"\t");
            strcat(tmp,data_segment[j]);
            strcat(tmp,"\n");
            write_next_line(tmp);

        }
        close_write();
    }

    if(enc)
    {
        create_file(".ent");
        for(j=0;j<enc;j++)
        {
            strcpy(tmp,enteries[j]);
            strcat(tmp,"\n");
            write_next_line(tmp);
        }
        close_write();
    }
    if(exc)
    {
        create_file(".ext");
        for(j=0;j<exc;j++)
        {
            strcpy(tmp,externals[j]);
            strcat(tmp,"\n");
            write_next_line(tmp);
        }
        close_write();
    }
}
void compile()
{
    errors_check();
    if(!if_error())
    {
        create_data();
        create_instructions();
        if(ic+dc>256)
            report_warning(4,0);
        create_enteris();
        create_labels();
        /**output();*/
        output_files();
    }
}
