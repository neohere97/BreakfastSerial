/***************************************************************************
 * Breakfast Serial
 * Author: Chinmay Shalawadi
 * Institution: University of Colorado Boulder
 * Mail id: chsh1552@colorado.edu
 * References: lecture slides & White Textbook
 ***************************************************************************/
#ifndef COMMAND_PROC

#define LINEBUFFER_LENGTH 100
/***********************************************************************************
 * function : Gets one line of data from the terminal and handles white space and backspace
 * parameters : *line -> destination location to store final line data
 * return : none
 ***********************************************************************************/
void line_accumulator(char line[]);
/***********************************************************************************
 * function : Parses the line into commands and calls the relevant command handler
 * parameters : *input -> source line data accumulated by line accumulator
 * return : none
 ***********************************************************************************/
void process_command(char *input);

#endif