
/***************************************************************************
 * Breakfast Serial
 * Author: Chinmay Shalawadi
 * Institution: University of Colorado Boulder
 * Mail id: chsh1552@colorado.edu
 * References: lecture slides & White Textbook
 ***************************************************************************/

#include "MKL25Z4.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "cbfifo.h"

// ---------------------------------------------------------TEST-CBFIFO------------------------------------------------

int test_cbfifo(int buff_no)
{
    // These static data is used to test the buffer and the results
    char *str_store = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefoxatethedogbrutally";
    char str[128] = {""};

    int passed_count = 0;
    int passed = 1;

    // Various test cases, queueing and dequeing cycles and length check.

    cbfifo_enqueue(buff_no, str_store, 500);
    if (cbfifo_length(buff_no) == 255)
        passed_count++;
    else
        passed = 0;

    cbfifo_dequeue(buff_no, str, 10);
    if (cbfifo_length(buff_no) == 245)
        passed_count++;
    else
        passed = 0;

    cbfifo_dequeue(buff_no, str, 50);
    if (cbfifo_length(buff_no) == 195)
        passed_count++;
    else
        passed = 0;

    cbfifo_dequeue(buff_no, str, 68);
    if (cbfifo_length(buff_no) == 127)
        passed_count++;
    else
        passed = 0;

    cbfifo_enqueue(buff_no, str_store, 50);
    if (cbfifo_length(buff_no) == 177)
        passed_count++;
    else
        passed = 0;

    cbfifo_dequeue(buff_no, str, 0);
    if (cbfifo_length(buff_no) == 177)
        passed_count++;
    else
        passed = 0;

    cbfifo_enqueue(buff_no, str_store, 1);
    if (cbfifo_length(buff_no) == 178)
        passed_count++;
    else
        passed = 0;

    cbfifo_dequeue(buff_no, str, 5);
    if (cbfifo_length(buff_no) == 173)
        passed_count++;
    else
        passed = 0;

    cbfifo_enqueue(buff_no, str_store, 127);
    if (cbfifo_length(buff_no) == 255)
        passed_count++;
    else
        passed = 0;

    cbfifo_dequeue(buff_no, str, 128);
    if (cbfifo_length(buff_no) == 127)
        passed_count++;
    else
        passed = 0;

    cbfifo_reset(TX_CBFIFO);
    cbfifo_reset(RX_CBFIFO);

    return passed;
}

// ------------------------------------------------run-fifo-tests------------------------------------------------------------
/***********************************************************************************
 * function : Funciton runs the RX and TX FIFO Tests and prints the result
 * parameters : none
 * return : none
 ***********************************************************************************/
void run_fifo_tests()
{

    int cbfifo_res_rx = test_cbfifo(RX_CBFIFO);
    int cbfifo_res_tx = test_cbfifo(TX_CBFIFO);

    if (cbfifo_res_rx)
    {
        printf("All test cases passed RX_CBFIFO\r\n");
    }
    else
    {
        printf("Some cases failed RX\n\r");
    }

    if (cbfifo_res_tx)
    {
        printf("All test cases passed TX_CBFIFO\r\n");
    }
    else
    {
        printf("Some cases failed TX\n\r");
    }
}
// ------------------------------------------------End------------------------------------------------------------
