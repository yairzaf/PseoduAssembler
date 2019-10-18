#include "error_report.h"
#include <stdlib.h>
#include <stdio.h>
#define ERRORS 18
#define WARNINGS 10
#define LENGTH 80


#define ERROR0 "Default error."
#define ERROR1 "File doesn't exist, or can't access (check privileges)."
#define ERROR2 "Empty File."
#define ERROR3 "Line too long."
#define ERROR4 "Label too long."
#define ERROR5 "Label already defined."
#define ERROR6 "Bad number declartion."
#define ERROR7 "Unexpected charcter."
#define ERROR8 "Unknown command."
#define ERROR9 "Expected arguments."
#define ERROR10 "Unexpected arguments."
#define ERROR11 "Bad argument."
#define ERROR12 "Bad sepration."
#define ERROR13 "Bad Label"
#define ERROR14 "Bad string declartion"
#define ERROR15 "can't use illegal label."
#define ERROR16 "illegal destination operand."
#define ERROR17 "illegal source operand."


#define WARN0 "default warning."
#define WARN1 "Loss of data, overflow."
#define WARN2 "illegal label placement,label isn't added."
#define WARN3 "program exceeds memory size of native architacture ."

char error_list[ERRORS][LENGTH]={ERROR0,ERROR1,ERROR2,ERROR3,ERROR4,ERROR5,ERROR6,ERROR7,ERROR8,ERROR9,ERROR10,ERROR11,ERROR12,ERROR13,ERROR14,ERROR15,ERROR16,ERROR17};
char warning_list[WARNINGS][LENGTH]={WARN0,WARN1,WARN2,WARN3};

int error_count=0;
int warning_count=0;

void reset_error_report()
{
    error_count=0;
    warning_count=0;
}
void report_error(int e,int l)
{
    error_count++;
    if(l)
        printf("line %d: ",l);
    printf("Error: %s\n",error_list[e]);
}
void report_warning(int w,int l)
{
    warning_count++;
    if(l)
        printf("line %d: ",l);
    printf("Warning: %s\n",warning_list[w]);

}
int if_error()
{
    return error_count;
}
void summary_report()
{
    if(error_count)
        printf("FAILED COMPILATION.\n");
    else
        printf("SUCCESSFUL COMPILATION.\n");
    printf("%d error(s), %d warning(s).\n",error_count,warning_count);
}
