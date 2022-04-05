#ifndef UART0_H

#include <stdint.h>

void uart_init();
uint32_t UART0_Read_Nonblocking();
void UART0_Send_Blocking(const char *msg);

#endif