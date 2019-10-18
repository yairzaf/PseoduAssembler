/**
    this handles the error messages
*/


#ifndef ERROR_REPORT_H
#define ERROR_REPORT_H

void reset_error_report();
/**
    resets the error and warning counters.
*/

void report_error(int e,int l);
/**

    prints error message corresponding to the given number
    int e - error number
    int l - line number , if zero wont print a line number
*/

void report_warning(int w,int l);
/**

    prints warning message corresponding to the given number
    int w - warning number
    int l - line number , if zero wont print a line number
*/
int if_error();
/**
    returns error number(used as a boolean)
*/

void summary_report();
/**
    will run post processing of the file
    prints if the compilation was successful or a failed one. (according to if there were any errors)
    prints how many errors and warnings

*/
#endif
