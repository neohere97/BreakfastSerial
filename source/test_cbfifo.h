/***************************************************************************
 * Breakfast Serial
 * Author: Chinmay Shalawadi
 * Institution: University of Colorado Boulder
 * Mail id: chsh1552@colorado.edu
 * References: lecture slides & White Textbook
 ***************************************************************************/

#ifndef TEST_CBFIFO_H
#define TEST_CBFIFO_H
// declaraions of the shared functions which can be accessed by main.c

/***********************************************************************************
 * function : Funciton runs the RX and TX FIFO Tests and prints the result
 * parameters : none
 * return : none
 ***********************************************************************************/
int test_cbfifo(int buff_no);

void run_fifo_tests();

#endif

// ------------------------------------------------End------------------------------------------------------------
