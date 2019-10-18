
/**
holds the program as an int array
*/
#ifndef COMPILER_H
#define COMPILER_H

#define LABEL_SIZE 31
#define NUM_OF_REGS 8
#define NUM_OF_OPS 16
#define NUM_OF_SPECS 4

int label_counter;
int ext_counter;
int num_counter;
int program_pointer;
int data_pointer;
/** counters for the different lists*/

extern char regs[NUM_OF_REGS][3];
extern char ops[NUM_OF_OPS][5];
extern char specs[NUM_OF_SPECS][8];
/** static lists of the already defined key words*/

char **labels;
char **externs;
char **numbers;
/**lists of the user defined operations */

int **data;
/**data array*/
int **program;
/**instructions and arguments represents by numbers*/

void compiler_reset();
/**wipes previous data for the next use*/

void compiler_end();
/**free allocated memory*/

void add_label(char *lab);
void add_ext(char *ext);
void add_num(char *numb);
void add_command(int *command);
void add_data(int *data_ar);
/**add to the list arguments and data*/

int get_label(char *l);
int get_ext(char *x);
int get_reg(char *r);
int get_op(char *o);
int get_spec(char *s);
int get_num(char *n);
/**returns the index of a specific users added data or a already defined words*/
#endif
