/***************************************************************************
 * Breakfast Serial
 * Author: Chinmay Shalawadi
 * Institution: University of Colorado Boulder
 * Mail id: chsh1552@colorado.edu
 * References: lecture slides & White Textbook
 ***************************************************************************/

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
#include "command_processor.h"


// ------------------------------------------------user-interface-lcd------------------------------------------------------------
/***********************************************************************************
 * function : shows the LCD menu and waits from user input
 * parameters : none
 * return : none
 ***********************************************************************************/
int main(void)
{
  //Initialize clocka and UART
  sysclock_init();
  uart_init();

  //Run the CBFIFO tests in Debug mode
  #ifdef DEBUG
  run_fifo_tests();
  #endif

  //Line buffer to hold line contents
  char line[LINEBUFFER_LENGTH] = {""};

  //Command processor loop
  while (1)
  {
    printf("\n\r? ");
    line_accumulator(line);
    process_command(line);
  }
  return 0;
}

// ------------------------------------------------End-------------------------------------------------------------
