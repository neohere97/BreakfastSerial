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
#include "test_cbfifo.h"

int main(void)
{
  sysclock_init();
  char text;
  // char test[30] = "HELLOWORLD helloworld\n\r";
  volatile int len = 0;
  uart_init();
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
  // cbfifo_reset(TX_CBFIFO);
  // cbfifo_reset(RX_CBFIFO);

  // printf("test\n\r");

  while (1)
  {
    int a = getchar();
    if (a){
      // printf("%c\n\r", a);
      if(a == 0x3F)
       printf("Chinmay Shalawadi\n\r");
    }
     
      printf("%c", a);
    // len = cbfifo_length();

    for (int i = 0; i < 10000; i++)
    {
    }
    // if(!len)
    // else{
    //   cbfifo_dequeue(&text,1);
    //   UART0_Send_Blocking(&text);
    // }
  }

  return 0;
}
