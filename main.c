/*
 * main.c - application entry point
 *
 * Author Howdy Pierce, howdy.pierce@colorado.edu
 */
#include "sysclock.h"
#include "MKL25Z4.h"
#include "uart0.h"
#include "cbfifo.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "test_cbfifo.h"

void line_accumulator(char line[]);
void handle_author(int argc, char *argv[]);
void handle_hexdump(int argc, char *argv[]);
void handle_help(int argc, char *argv[]);
void process_command(char *input);
char *hexdump(char *str, size_t size, const void *loc, size_t nbytes);
int uint_to_hexstr(char *str, size_t size, uint32_t num, uint8_t nbits);

typedef void (*command_handler_t)(int, char *argv[]);

typedef struct
{
  const char *name;
  command_handler_t handler;
  const char *help_string;
} command_table_t;

static const command_table_t commands[] = {
    {"author", handle_author, "Prints Author's Name"},
    {"dump", handle_hexdump, "Dump of memory, give starting location, Length"},
    {"help", handle_help, "Lists all the commands supported"}};

static const int num_commands =
    sizeof(commands) / sizeof(command_table_t);

int main(void)
{
  sysclock_init();
  uart_init();
  run_fifo_tests();

  char line[100] = {""};

  while (1)
  {
    printf("\n\r? ");
    line_accumulator(line);

    process_command(line);
  }
  return 0;
}

void line_accumulator(char *line)
{
  int i = 0;
  char *data = line;
  char byte = 0;
  int backspace_count = 0;
getmorechars:
  byte = getchar();
  if (byte > 0)
  {
    if (byte != 0xD)
    {
      if (byte == 0x20)
        backspace_count++;

      if (byte == 0x8 && i)
      {
        i -= 1;
      }

      if (backspace_count <= 1 && byte != 0x8)
      {
        data[i++] = byte;
        if (byte != 0x20)
          backspace_count = 0;
      }
      else if (byte != 0x20 && byte != 0x8)
      {
        data[i++] = byte;
        backspace_count = 0;
      }
      goto getmorechars;
    }
    else
    {
      data[i++] = 0x20;
      data[i++] = '\0';
    }
  }
  else
  {
    goto getmorechars;
  }
}

void process_command(char *input)
{
  char *p = input;
  char *end;
  char *temp;
  // find end of string
  for (end = input; *end != '\0'; end++)
    ;
  // Tokenize input in place
  char *argv[10];
  int argc = 0;
  memset(argv, 0, sizeof(argv));

  temp = input;
  for (p = input; p < end; p++)
  {
    if (*p == 0x20)
    {
      *p = 0;
      argv[argc++] = temp;
      temp = (p + 1);
    }
  }
  argv[argc] = NULL;
  if (argc == 0) // no command
    return;
  int unknown_command = 1;

  for (int i = 0; i < num_commands; i++)
  {
    if (strcasecmp(argv[0], commands[i].name) == 0)
    {
      commands[i].handler(argc, argv);
      unknown_command = 0;
      break;
    }          
  }

  if(unknown_command)
  printf("\n\n\rUnknown Command: %s\n\n\rUse 'help' for list of commands\n\r", argv[0]);
 
}

void handle_author(int argc, char *argv[])
{
  printf("\n\rChinmay Shalawadi\n\r");
};

void handle_help(int argc, char *argv[])
{
  printf("\n\n\r  Commands Supported\n\n\r");
  for (int i = 0; i < num_commands; i++)
  {
    printf("  %s -> ", commands[i].name);
    printf("%s\n\n\r", commands[i].help_string);
  }
}

void handle_hexdump(int argc, char *argv[])
{
  char *stri = "The quick brown fox jumped over the lazy dog. THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG.";
  // Char storage to store returned string
  char hexdump_text[3000] = {""};
  hexdump(hexdump_text, 3000, stri, 50);

  printf("\n\rHexdump\n\r");
  printf("%s\n\n\r", hexdump_text);
}

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
    int address_offset_counter = 0;
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
      uint_to_hexstr(off, 100, address_offset_counter, 16);
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
    str[count2++] = hex_reverse_array[i];
  }
  str[count2++] = '\0';
  // Returning the total characters written without \0
  return count + 2;
}