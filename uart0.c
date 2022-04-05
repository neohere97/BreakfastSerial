#include "uart0.h"
#include "MKL25Z4.h"
#include "cbfifo.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define UART_OVERSAMPLE_RATE 16
#define SYS_CLOCK 24000000
#define BAUD_RATE 38400

void uart_init()
{

    uint16_t sbr;

    // Enable UART0 Clock
    SIM->SCGC4 |= SIM_SCGC4_UART0(1);

    // Enable PORTA clock
    SIM->SCGC5 |= SIM_SCGC5_PORTA(1);

    UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

    // Select MCGFLLCLK as UART0 clock
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
    SIM->SOPT2 &= ~(SIM_SOPT2_PLLFLLSEL_MASK);

    PORTA->PCR[1] |= PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); /* PTA1 as ALT2 (UART0) */
    PORTA->PCR[2] |= PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); /* PTA2 as ALT2 (UART0) */

    sbr = (uint16_t)((SYS_CLOCK) / (BAUD_RATE * UART_OVERSAMPLE_RATE));
    UART0->BDH &= ~UART0_BDH_SBR_MASK;
    UART0->BDH |= UART0_BDH_SBR(sbr >> 8); // sets BDH and configures UART in 2 stop bit mode
    UART0->BDH |= UART0_BDH_SBNS(1) | UART0_BDH_LBKDIE(0) | UART0_BDH_RXEDGIE(0);
    UART0->BDL = UART0_BDL_SBR(sbr);
    UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE - 1);

    // Configure Serial Port as 8-N-1
    // (8 data bits, No parity and 1 stop bit)
    UART0->C1 = 0x00;

    // // Configure Tx/Rx Interrupts
    UART0->C2 |= UART_C2_TIE(0);  // Tx Interrupt disabled
    UART0->C2 |= UART_C2_TCIE(0); // Tx Complete Interrupt disabled
    UART0->C2 |= UART_C2_RIE(1);  // Rx Interrupt enabled
    // Configure Transmitter/Receiever
    UART0->C2 |= UART_C2_TE(1); // Tx Enabled
    UART0->C2 |= UART_C2_RE(1); // Rx Enabled

    // // Enable UART0 Interrupt
    NVIC_EnableIRQ(UART0_IRQn);
}

uint32_t UART0_Read_Nonblocking()
{
    while (1)
    {
        if (UART0->S1 & UART0_S1_RDRF_MASK)
            return UART0->D;
    }
    //   return -1;
}

void UART0_Send_Blocking(const char *msg)
{
    while (*msg)
    {
        while (!(UART0->S1 & UART0_S1_TDRE_MASK))
            ;
        UART0->D = *msg++;
    }
}

int __sys_write(int handle, char *buf, int size)
{

    int count = 0,count2=0;   
    while(size){
        NVIC_DisableIRQ(UART0_IRQn);
        count2 = cbfifo_enqueue(TX_CBFIFO, &buf[count], size);
        NVIC_EnableIRQ(UART0_IRQn);
         if (~(UART0->C2 & UART0_C2_TIE_MASK))
        UART0->C2 |= UART_C2_TIE(1);
        count += count2;       
        size-=count2;        
    }
    return 0;
}

int __sys_readc(void)
{
    uint8_t byte ;    
    if (cbfifo_dequeue(RX_CBFIFO, &byte, 1))
        return byte;
    else
        return 0;
}

void UART0_IRQHandler(void)
{
    NVIC_DisableIRQ(UART0_IRQn);
    uint8_t byte;
    const uint8_t error_flags = UART_S1_OR_MASK | UART_S1_NF_MASK |
                                UART_S1_FE_MASK | UART_S1_PF_MASK;

    if (UART0->S1 & error_flags)
    {
        // We're in error. We should probably increment an error counter. For now
        // clear the flags, and also read the data register to clear RDRF
        UART0->S1 |= error_flags;
        byte = UART0->D;
    }
    if (UART0->S1 & UART0_S1_RDRF_MASK)
    { // byte ready to be read; enqueue it
        byte = UART0->D;
        cbfifo_enqueue(RX_CBFIFO, &byte, 1);
        // If there was no room on the FIFO, this byte just got silently
        // dropped. Whoops. Maybe we should increment an error counter?
    }
    if ((UART0->C2 & UART0_C2_TIE_MASK) && // transmitter interrupt enabled
        (UART0->S1 & UART0_S1_TDRE_MASK))
    { // tx buffer empty
        if (cbfifo_dequeue(TX_CBFIFO, &byte, 1))
        { // a byte is waiting to tx
            UART0->D = byte;
        }
        else
        { // FIFO was empty, so disable transmitter interrupt
            UART0->C2 &= ~UART0_C2_TIE_MASK;
        }
    }
    NVIC_EnableIRQ(UART0_IRQn);
}