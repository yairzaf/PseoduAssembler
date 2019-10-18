/**
    this handles the text phrasing of the assembly file.
    translating it into array of ints
*/
#ifndef CODE_PHRASE_H
#define CODE_PHRASE_H
#include "compiler.h"
#include "file_handle.h"
#include "error_report.h"

#define SKIP_WHITE_SPACE(index)\
{\
    while((line[index]==' '||line[index]=='\t')&&index<=LINE_SIZE)\
        index++;\
}

#define SKIP_CHAR_SPACE(index)\
{\
    while((line[index]!=' '&&line[index]!='\t'&&line[index]!='\0'&&line[index]!='\n')&&index<=LINE_SIZE)\
            index++;\
}


int line_counter;
/** current line */
int line_index;
/** global line index*/

char tmp[LINE_SIZE];
/** different string jobs if needed */

char **dissected;
/** stores array of the divided line*/


int command[6];
/** 0-label: 1-operation 2-label_argument  3-argument1 4-argument2 5-line */


void phrase_files(char *argv[]);
/** pass on all given files*/


void process_file();
/** handle the current file */

void read_file();
/** read the contents of the current file */

void stage_1();
/** get all labels and numbers(user defined stuff) */
void stage_2();
/** phrase the textual code into array of numbers representing it*/



void phrase_line_1();
void phrase_line_2();
/** handles the lines in each stage*/


int empty_line();
int end_of_line();
/** boolean for is it the end of line or is it an empty one */


void find_label();
void find_extern(int n);
void find_num(int n);
/** find labels and numbers on first stage and save them into a list */


int dissect_command();
/** divide the line into  white spaces and separation symbols ( ":" "," "(" ")" " " "\t" ) and return how many tokens have been created */


int process_command(int num);
/** get how many parts the command consist of and process it (get only the declaration of label and operations\specifications ) */

void process_arguments(int num);
/** get how many parts the command consist of and process it (complete the arguments of the operations ) */

int get_arg(char *a);
/** gets an argument and returns it */

int get_string(int position);
/** adds a string to the data array*/
int get_data(int position,int num);
/** adds a number sequence to the data array*/
#endif
