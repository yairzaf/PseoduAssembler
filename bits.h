
/**
    holds data in a binary format.
*/

#ifndef BITS_H
#define BITS_H
#define WORD_SIZE 14
#define OFFSET 100
char binary[WORD_SIZE];
/**char array to represent a word in the native machine*/

int ic,dc,exc,enc;
/**instruction counter, data counter, externals counter, entries counter*/

char **instruction_segment;
char **data_segment;
char **externals;
char **enteries;
/**lists of instructions data externals entries */

void binary_reset();
/**wipe previous data for next use*/

void binary_end();
/**free allocated memory*/


int **label_adress;
int address_counter;
void add_address(int adr);
/** address corresponding to each label*/

void add_instructions(char *ins);
void add_data_seg(char *dat);
void add_externals(char *ext);
void add_enteries(char *ent);
/** add instructions, data, external, entries, to each segment*/

void create_binary(int n);
/** generate a binary word into "bin" from an int*/

int over_flow(int n);
/** returns 1 if an int is overflowing "bin" */

void errors_check();


void create_data();
/**generate data segment*/

void create_instructions();
/**generate instruction segment */

int arg_type(int arg);
/**get type of arg*/

int create_arg(int arg,int p);
/**generate binary of an argument*/

void create_labels();
/** add label addresses to the instruction segment and generate externals*/

void create_enteris();
/**generate entries*/

void compile();
/**generate complete program*/

void output();

void output_files();
/** output program to files if no errors*/
#endif

