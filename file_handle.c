#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "file_handle.h"

FILE *fp_r;
FILE *fp_w;


int file_counter=1;
void next_file(char *argv[])
{
    if(argv[file_counter]!=NULL)
    {
        strcpy(file_name,argv[file_counter]);

        file_counter++;
    }
    else
        strcpy(file_name,"END");
}
int open_file()
{

    strcat(file_name,".as");

    if(access(file_name,R_OK) == -1)
    {

        return 0;
    }
    else
    {
        fp_r=fopen(file_name,"r");
        file_name[strlen(file_name)-3]='\0';
        return 1;
    }

}
void reset_read()
{
    fseek(fp_r, 0, SEEK_SET);
}
void close_file()
{

    fclose(fp_r);
}
void get_next_line()
{
    if(!fgets(line,LINE_SIZE,fp_r))
        strcpy(line,"EOF");

}
int create_file(char *type)
{

    strcat(file_name,type);
    fp_w=fopen(file_name,"w");
    file_name[strlen(file_name)-strlen(type)]='\0';
    return 1;
}
void reset_write()
{
    fseek(fp_w, 0, SEEK_SET);
}
void close_write()
{
    fclose(fp_w);
}
void write_next_line(char *w)
{
    fputs(w, fp_w);
}
