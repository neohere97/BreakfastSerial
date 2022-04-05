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
  uart_init();
  run_fifo_tests();

  while (1)
  {
    int a = getchar();
    if (a){
      // printf("%c\n\r", a);
      if(a == 0x3F){
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-\n\rabcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-\n\rabcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-\n\rabcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-\n\rabcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-\n\rabcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-\n\rabcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-\n\r");
 
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-,thequickbrownfoxjumpedoverthelazydogandthefox\n\r");
       printf("abcdefghijklmnopqrabcdefghijklmnopqrstuvwxyzABCDEFGHIJKL\n\r");
       printf("MNOPQRSTUVWXYZ0123456789*\n\r");
      }
       printf("%c", a);
    }
     
      
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
