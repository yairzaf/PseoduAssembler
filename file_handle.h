/**
    this handles the file i\o for the text phrasing of the assembly code

*/
#ifndef FILE_HANDLE_H
#define FILE_HANDLE_H
#define LINE_SIZE 80
char line[LINE_SIZE];
/** last line that was read from the file */

char file_name[64];
/** current file name that is given by the arguments. */

void next_file(char *argv[]);
/** gets the file names from the program arguments. */

int open_file();
/** try's to open for reading the current file (file_name) returns 1 if successful 0 if not. */
void reset_read();

void close_file();
/** closes the current assembly file stream thats being red. */

void get_next_line();
/** gets the next line from the current file thats being red.*/

int create_file(char *type);
/** creates a new output file with the name of the current file being red with a given ending (type - ".ob"/".ent"/".ext"), returns 1 if successful 0 if not.  */

void close_write();
/** closes the current output stream of an output file. */

void reset_write();

void write_next_line(char *w);
/** writes a new line to the current output file stream. */
#endif
