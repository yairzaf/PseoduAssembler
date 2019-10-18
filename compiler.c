#include "compiler.h"
#include "file_handle.h"
#include "bits.h"
#include "error_report.h"
#include "code_phrase.h"
#include <string.h>
#include <stdlib.h>

char regs[NUM_OF_REGS][3]={"r0","r1","r2","r3","r4","r5","r6","r7"};
char ops[NUM_OF_OPS][5]={"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","red","prn","jsr","rts","stop"};
char specs[NUM_OF_SPECS][8]={"data","string","entry","extern"};

void compiler_reset()
{
    label_counter=0;
    num_counter=0;
    ext_counter=0;
    program_pointer=0;
    data_pointer=0;
    labels=malloc(label_counter * sizeof(char *));
    externs=malloc(ext_counter * sizeof(char *));
    numbers=malloc(num_counter * sizeof(char *));
    program=malloc(program_pointer * sizeof(int *));
    data=malloc(data_pointer * sizeof(int *));
    binary_reset();

}
void compiler_end()
{

    free(labels);
    free(numbers);
    free(program);
    free(data);
    free(externs);

    binary_end();


}
void add_label(char *lab)
{
    label_counter++;
    labels=realloc(labels,label_counter * sizeof(char *));
    labels[label_counter-1]=(char *)malloc(sizeof(char)*LABEL_SIZE);
    strcpy(labels[label_counter-1],lab);

}
void add_ext(char *ext)
{
    ext_counter++;
    externs=realloc(externs,ext_counter * sizeof(char *));
    externs[ext_counter-1]=(char *)malloc(sizeof(char)*LABEL_SIZE);
    strcpy(externs[ext_counter-1],ext);
}
void add_num(char *numb)
{
    num_counter++;
    numbers=realloc(numbers,num_counter * sizeof(char *));
    numbers[num_counter-1]=(char *)malloc(sizeof(char)*LINE_SIZE);
    strcpy(numbers[num_counter-1],numb);
}
void add_command(int *command)
{
    int i;
    program_pointer++;
    program=realloc(program,program_pointer * sizeof(int *));
    program[program_pointer-1]=(int *)malloc(sizeof(int *)*6);
    for(i=0;i<6;i++)
        program[program_pointer-1][i]=command[i];
}
void add_data(int *data_ar)
{
    if(over_flow(data_ar[0]))
        report_warning(1,line_counter);
    int i;
    data_pointer++;
    data=realloc(data,data_pointer * sizeof(int *));
    data[data_pointer-1]=(int *)malloc(sizeof(int *)*1);
    for(i=0;i<1;i++)
        data[data_pointer-1][i]=data_ar[i];
}
int get_label(char *l)
{
    int i;
    for(i=0;i<label_counter && strcmp(labels[i],l);i++);
    if(i==label_counter)
        return -1;
    return 10+i;
}
int get_ext(char *x)
{
    int i;
    for(i=0;i<ext_counter && strcmp(externs[i],x);i++);
    if(i==ext_counter)
        return -1;
    return 10+label_counter+i;
}
int get_reg(char *r)
{
    int i;
    for(i=0;i<NUM_OF_REGS && strcmp(regs[i],r);i++);
    if(i==NUM_OF_REGS)
        return -1;
    return i;

}
int get_op(char *o)
{
    int i;
    for(i=0;i<NUM_OF_OPS && strcmp(ops[i],o);i++);
    if(i==NUM_OF_OPS)
        return -1;
    return i;
}
int get_spec(char *s)
{
    int i;
    for(i=0;i<NUM_OF_SPECS && strcmp(specs[i],s);i++);
    if(i==NUM_OF_SPECS)
        return -1;
    return i;
}
int get_num(char *n)
{
    int i;
    for(i=0;i<num_counter && strcmp(numbers[i],n);i++);
    if(i==num_counter)
        return -1;
    return (i+10)*(-1);
}
