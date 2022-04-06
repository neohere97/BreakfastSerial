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

// Print character definitions
#define CR 0xD
#define SPACE 0x20
#define BACKSPACE 0x8

// Function Declarations
void handle_author(int no_commands, char *command_list[]);
void handle_hexdump(int no_commands, char *command_list[]);
void handle_help(int no_commands, char *command_list[]);
char *hexdump(char *str, size_t size, const void *loc, size_t nbytes);
int uint_to_hexstr(char *str, size_t size, uint32_t num, uint8_t nbits);

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

// ------------------------------------------------hexdump-from-Assignment1----------------------------------------------------------
/***********************************************************************************
 * function : Generates hexdump string with location and number of bytes
 * parameters : *str -> destination buffer to store string
 *              size -> size of the destination buffer
 *              *loc -> Starting location for the dump
 *              nbytes -> Number of bytes to be dumped
 * return : pointer to the string destination
 ***********************************************************************************/

char *hexdump(char *str, size_t size, const void *loc, size_t nbytes)
{

  // Dereferencing the void pointer, declared as const becasue the parameter is also const
  const uint8_t *dump_loc = loc;

  // Initializing variables
  int total_memory_needed = 0;
  int total_rows = 0;

  // copy of nbytes
  int nbytes_copy = nbytes;
  int i;
  // calculating total rows using nbytes
  for (i = 1; i <= nbytes_copy; i++)
  {
    if (i == 1)
    {
      total_rows++;
    }
    if (i == 16)
    {
      i = 0;
      nbytes_copy = nbytes_copy - 16;
    }
  }

  // Calculating the total bytes required
  total_memory_needed = (total_rows * 7) + (nbytes * 3);
  // counter to write to the final string
  int finalStringCount = 0;

  if (size >= total_memory_needed && nbytes > 0)
  {
    // first column address counter
    int address_offset_counter = (int)loc;
    // initializing more counters and format variables
    int total_bytes_to_read_write = nbytes;
    int bytes_this_row = 0;

    // Temporary storage for Hex converted characters
    char off[100];
    char data[100];

    // Main For-Loop to go through all the rows
    for (int j = 0; j < total_rows; j++)
    {
      // converting address offset value to hex by calling the uint_to_hexstr function previously written
      // nbits is 16 to get 4  digit hex representation of address
      uint_to_hexstr(off, 100, address_offset_counter, 32);
      // ir is a general use counter variable to read through hex characters and adding to final string
      int ir = 0;
      while (off[ir] != '\0')
      {
        str[finalStringCount++] = off[ir++];
      }
      // Adding a space after writing the address column
      str[finalStringCount++] = ' ';

      // Assigning number of bytes to read_Write per row
      if (total_bytes_to_read_write > 16)
      {
        bytes_this_row = 16;
        total_bytes_to_read_write -= 16;
      }
      else
      {
        // If remaining bytes are less than 16, program will finish in this row
        bytes_this_row = total_bytes_to_read_write;
      }
      // Reading throguh bytes of memory location
      for (int i = 0; i < bytes_this_row; i++)
      {
        // conversion of raw binary data to hex strings
        uint_to_hexstr(data, 100, *dump_loc++, 8);
        // ir is 2 to not include the '0x' which is by default included by the uint to hexstr function
        ir = 2;
        while (data[ir] != '\0')
        {
          str[finalStringCount++] = data[ir++];
        }
        // Adding a space after the hex string if it's not the 16th byte in the row
        if (i + 1 != bytes_this_row)
          str[finalStringCount++] = ' ';
      }
      // Adding a new line character after 16 bytes in the row
      if (bytes_this_row == 16 && j + 1 != total_rows)
      {
        str[finalStringCount++] = '\n';
        str[finalStringCount++] = '\r';
      }
      // Incrementing the address offset counter by 16bytes
      address_offset_counter += 16;
    }
    // Adding null character to the end of the final string which needs to be returned
    str[finalStringCount++] = '\0';
    return str;
  }
  else
  {
    // Setting string to  null in case of error and returning the same
    str[0] = '\0';
    return str;
  }
}
// ------------------------------------------------uint-to-hexstr-Assignment-1--------------------------------------------------------
/***********************************************************************************
 * function : converts uint to hex string
 * parameters : *str -> string buffer to store the converted hex string
 *              size -> size of the buffer
 *               num -> number to be converted
 *             nbits -> number of bits in the hex string
 * return : none
 ***********************************************************************************/
int uint_to_hexstr(char *str, size_t size, uint32_t num, uint8_t nbits)
{

  char hex_reverse_array[nbits];
  int count = 0;
  // Checking if the size is enough to represent Hex characters
  if ((nbits >> 2) + 3 > size)
  {
    goto error;
  }
  // Checking if string pointer is null
  if (str == NULL)
    return -1;
  // Checking if nbits is one of the specific value, 4,8,16,32
  else if (nbits == 4 || nbits == 8 || nbits == 16 || nbits == 32)
  {
    while (num > 0)
    {
      // Extracting last 4 bits from the least significant byte by
      // using the Bitwise AND operation with 0xF
      uint32_t res = num & 0xF;

      if (res <= 9)
      {
        // Adding characters using ascii for numbers
        hex_reverse_array[count++] = (char)(res + 48);
      }
      else if (res >= 10 && res < 16)
      {
        // Adding characters using ascii for Letters
        hex_reverse_array[count++] = (char)(res + 55);
      }
      // Rigt shifting by 4 to access next 4 bits of the number
      num = num >> 4;
    }
    // Range check
    if ((count * 4) > nbits)
    {
      goto error;
    }
    else if (count < nbits)
    {
      // calculating extra zeros for hex representation
      int extra_zeros = (nbits - (count * 4)) >> 2;
      // Adding Extra zeros
      for (int i = 0; i < extra_zeros; i++)
      {
        hex_reverse_array[count++] = '0';
      }
    }
  }
  else
  {
  // Error Block
  error:
    str[0] = '\0';
    return -1;
  }
  // Adding hex identifiers
  str[0] = '0';
  str[1] = 'x';
  int count2 = 2;
  // Reversing the reversed array and adding to the string
  for (int i = count - 1; i >= 0; i--)
  {
    if (i == 3)
      str[count2++] = '_';

    str[count2++] = hex_reverse_array[i];
  }
  str[count2++] = '\0';
  // Returning the total characters written without \0
  return count + 2;
}

// ------------------------------------------------End------------------------------------------------------------
