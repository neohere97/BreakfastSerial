
#include "MKL25Z4.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "cbfifo.h"
#include "commons.h"

// These static data is used to test the buffer and the results
char *str_store = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefoxatethedogbrutally";
char str[128] = {""};

// The core buffer variables definied in the CB Buffer file,
//  They are used here for testing purposes
extern uint8_t cb_buffer[];
extern uint8_t read_index;
extern uint8_t write_index;
extern uint8_t end_index;

// ---------------------------------------------------------TEST-CBFIFO------------------------------------------------

int test_cbfifo(int buff_no)
{

    // printf("Starting CBFIFO Tests...\n\n\r");    

    int passed_count = 0;
    int passed = 1;

    // Various test cases, queueing and dequeing cycles and length check.

    // printf("Capacity of the  buffer is -> %lu \n\n\r", cbfifo_capacity());
    // printf("Enqueueing 500 Bytes of Data, Bytes actually Queued");
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

    // printf("CASES PASSED %d/10 \n \n\r", passed_count);

    return passed;
}

/*
Below function is just for debugging, to dumpt the contents of the buffer to crosscheck
*/

void run_fifo_tests(){
  int cbfifo_res_rx = test_cbfifo(RX_CBFIFO);
  int cbfifo_res_tx = test_cbfifo(TX_CBFIFO);


  if (cbfifo_res_rx & cbfifo_res_tx)
  {
    printf("All test cases passed, both RX and TX Buffers \r\n");
  }
  else
  {
    printf("Some cases failed\n\r");
  }
}