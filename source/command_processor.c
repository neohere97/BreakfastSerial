/***************************************************************************
 * Breakfast Serial
 * Author: Chinmay Shalawadi
 * Institution: University of Colorado Boulder
 * Mail id: chsh1552@colorado.edu
 * References: lecture slides & White Textbook & Assignment 1 (Hexdump)
 ***************************************************************************/

#include "command_processor.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "hexdump.h"

// Print character definitions
#define CR 0xD
#define SPACE 0x20
#define BACKSPACE 0x8

// Function Declarations
void handle_author(int no_commands, char *command_list[]);
void handle_hexdump(int no_commands, char *command_list[]);
void handle_help(int no_commands, char *command_list[]);


// function pointer definitions
typedef void (*command_handler_t)(int, char *command_list[]);

// command struct definition
typedef struct
{
  const char *name;
  command_handler_t handler;
  const char *help_string;
} command_table_t;

// commands available
//New commands can be added very easily by adding an entry to the table
//and adding a command handler function
static const command_table_t commands[] = {
    {"author", handle_author, "Prints Author's Name"},
    {"dump", handle_hexdump, "Dump of memory, give starting location, Length"},
    {"help", handle_help, "Lists all the commands supported"}};

static const int num_commands =
    sizeof(commands) / sizeof(command_table_t);

// ------------------------------------------------line-accumulator-----------------------------------------------------------
/***********************************************************************************
 * function : Gets one line of data from the terminal and handles white space and backspace
 * parameters : *line -> destination location to store final line data
 * return : none
 ***********************************************************************************/
void line_accumulator(char *line)
{
  // index variable used to write to the buffer
  int i = 0;

  char *data = line;
  // input data byte definiton
  char byte = 0;
  // counter to handle multiple white spaces
  int space_count = 0;

// Instead of a while loop, a label and goto statements are used for input
getmorechars:
  byte = getchar();
  // if valid byte is available
  if (byte > 0)
  {
    // Check to see if the byte is not equal to Carriage Return
    if (byte != CR)
    {
      // Update space counter
      if (byte == SPACE)
        space_count++;

      // If backspace is hit and i>0
      if (byte == BACKSPACE && i)
      {
        i -= 1;
      }
      // Adding character to line if its not backspace and leading spaces
      if (space_count <= 1 && byte != BACKSPACE && i != 0)
      {
        data[i++] = byte;
        if (byte != SPACE)
          space_count = 0;
      }
      // Adding characters to the line if its not space or backspace
      else if (byte != SPACE && byte != BACKSPACE)
      {
        data[i++] = byte;
        space_count = 0;
      }
      goto getmorechars;
    }
    else
    {
      // Adding an extra space and null terminator
      // Extra space is added for the command parser
      data[i++] = SPACE;
      data[i++] = '\0';
    }
  }
  else
  {
    // when no valid data byte is available go back to get more characters
    goto getmorechars;
  }
}
// ------------------------------------------------process-command-----------------------------------------------------------
/***********************************************************************************
 * function : Parses the line into commands and calls the relevant command handler
 * parameters : *input -> source line data accumulated by line accumulator
 * return : none
 ***********************************************************************************/
void process_command(char *input)
{
  char *p = input;
  char *end;
  char *temp;
  // find end of string
  for (end = input; *end != '\0'; end++)
    ;
  // Tokenize input in place
  char *command_list[10];
  int no_commands = 0;

  // initializing all the values to 0
  memset(command_list, 0, sizeof(command_list));

  // temp used to store locations of every word start
  temp = input;
  for (p = input; p < end; p++)
  {
    // Replacing the space character with \0 and storing the pointer to the begining
    // in the command_list array
    if (*p == SPACE)
    {
      *p = 0;
      command_list[no_commands++] = temp;
      temp = (p + 1);
    }
    // If there are too many argument entered by the user
    if (no_commands > 3)
    {
      printf("\n\rError: Too many commands/arguments \n\r");
      return;
    }
  }

  command_list[no_commands] = NULL;
  // If no command is sent
  if (no_commands == 0)
  {
    printf("\n\rError: No Command Sent \n\r");
    return;
  }

  // Flag to check if a valid command is written
  int unknown_command = 1;

  // Find the matching command and dispatch the command handler
  for (int i = 0; i < num_commands; i++)
  {
    if (strcasecmp(command_list[0], commands[i].name) == 0)
    {
      commands[i].handler(no_commands, command_list);
      // updating the unknown command flag
      unknown_command = 0;
      break;
    }
  }

  if (unknown_command)
    printf("\n\n\rUnknown Command: %s\n\n\rUse 'help' for list of commands\n\r", command_list[0]);
}
// ------------------------------------------------handle-author-----------------------------------------------------------
/***********************************************************************************
 * function : prints the author
 * parameters : no_commands -> count variable of command array
 *              command_list -> pointers to list of commands
 * return : none
 ***********************************************************************************/
void handle_author(int no_commands, char *command_list[])
{
  printf("\n\rChinmay Shalawadi\n\r");
};
// ------------------------------------------------handle-help-----------------------------------------------------------
/***********************************************************************************
 * function : Prints all the commands with their help text
 * parameters : no_commands -> count variable of command array
 *              command_list -> pointers to list of commands
 * return : none
 ***********************************************************************************/
void handle_help(int no_commands, char *command_list[])
{
  printf("\n\n\r  Commands Supported\n\n\r");
  for (int i = 0; i < num_commands; i++)
  {
    printf("  '%s' -> ", commands[i].name);
    printf("%s\n\n\r", commands[i].help_string);
  }
}
// ------------------------------------------------handle-hexdump-----------------------------------------------------------
/***********************************************************************************
 * function : command handler for command dump
 * parameters : no_commands -> count variable of command array
 *              command_list -> pointers to list of commands
 * return : none
 ***********************************************************************************/
void handle_hexdump(int no_commands, char *command_list[])
{
  // storage for hexdump string which gets generated
  char hexdump_text[3200] = {""};
  // variable to store the starting location of the hexdump
  int *startloc;
  int numbytes;

  // parse start location treating it as hex
  sscanf(command_list[1], "%x", &startloc);

  // parse length based on the representation
  if (*(command_list[2] + 1) == 'x')
    sscanf(command_list[2], "%x", &numbytes);
  else
    sscanf(command_list[2], "%d", &numbytes);

  // max length check
  if (numbytes <= 640)
  {
    //generating the hexdump
    hexdump(hexdump_text, 5000, startloc, numbytes);
    printf("\n\n\r");
    puts(hexdump_text);
    printf("\n\n\r");
  }
  else
  {
    printf("\n\r Error : Length too long\n\r");
  }
}


// ------------------------------------------------End------------------------------------------------------------
