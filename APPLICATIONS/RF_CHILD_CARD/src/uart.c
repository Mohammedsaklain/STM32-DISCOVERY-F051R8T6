#include "rcc.h"
#include "uart.h"

void Init_UART(void)
{
    /* Clearing Required Bits in USART_CR1 control Reg*/
    USART2->CR1 &= ~(   (1<<28) | /* Clearing M1 for 1-SB, 8-DB (28)*/
                        (3U<<26) | /* Interrupts Inhibited       (27-26)*/
                        (1<<15) | /* Oversampling mode 16x      (15)*/
                        (1<<14) | /* Inhibit Interrupt          (14)*/
                        (1<<13) | /* RX active mode permanent   (13)*/
                        (1<<12) | /* Clearing M0 for 1-SB, 8-DB (12)*/
                        (1<<10) | /* Parity control disabled    (10)*/
                        (0x1F<<4) | /* Inhibit Interruts        (8-4)*/
                        (1<<3)  | /* Don't Enable TX Just Yet   (3)*/
                        (1<<2)  | /* Don't Enable RX Just Yet   (2)*/
                        (1<<0));  /* Don't Enable UART Just Yet (1)*/

    /* Clearing Required Bits in USART_CR2 control Reg*/
    USART2->CR2 &= ~(   (1<<23) | /* Disable Receiver Timeout   (23)*/
                        (1<<20) | /* Disable Auto baudrate      (20)*/
                        (1<<19) | /* Send LSB First             (19)*/
                        (1<<17) | /* Idle state for TX(HIGH)    (17)*/
                        (1<<16) | /* Idle state for RX(HIGH)    (16)*/
                        (1<<15) | /* No swapping of TX/RX func  (15)*/
                        (1<<14) | /* Disable LIN                (14)*/
                        (3U<<12) | /* Use of 1 - STOP bit        (13-12)*/
                        (1<<11) | /* Disabling CLK(CLK used for USART) (11)*/
                        (1<<6));  /* Inhibit LIN break Interrupt (6)*/

    /* Clearing Required Bits in USART_CR3 control Reg*/
    USART2->CR3 &= ~(   (1<<22) | /* Disabling Wakeup frm stop mode int (22)*/
                        (1<<14) | /* Disabling Driver mode              (14)*/
                        (3<<8)  | /* Disabling RTS & CTS                (9-8)*/
                        (0xF<<4)| /* Disabling DMAT, DMAR, SCEN, NACK   (7-4)*/
                        (0xB<<0)); /* Disabling HDSEL, IREN, EIE         (3,1,0)*/

    /* Setting Required Bits in USART_CR3 control Reg*/
    USART2->CR3 |= (    (1<<12) | /* Disable Overrun detection      (12)*/
                        (1<<11)); /* Select 1 Sample bit method     (11)*/

    /* set the baud rate value register*/
    USART2->BRR = 69; /* set for BD 115200, with 8MHz, and shifted [2-0] bits obtained to right 1 Pos*/

    /* Enable required bits in USART2_CR1*/
    USART2->CR1 |=   (USART_CR1_RXNEIE// Enable Receive Int.
                     |USART_CR1_TXEIE // Enable Transmit Int.
                     |USART_CR1_TE    // Enable Transmitter
                     |USART_CR1_RE    // Enable Receiver
                     |USART_CR1_UE);  // Enable UART2
    
    NVIC_EnableIRQ(USART2_IRQn);    // Enable USART2 Int.
}

/* ISR for UART2 
NOTE: All the int. occured for UART2 will be directed to here*/

void USART2_IRQHandler(void)
{
    uint8_t rxData = 0;
    /* Check if there is a data in RECEIVE DATA REGISTER*/
    // Here USART_ISR_RXNE is just a (1<<5) value
    if(USART2->ISR & USART_ISR_RXNE)
    {
        rxData = USART2->RDR;   // Store the data in temp variable

        USART2->TDR = rxData;   // Transmit again to received data
        // Wait till the data has been transferred 
        while(!USART2->ISR & USART_ISR_TC);
    }
    else if(USART3->ISR & USART_ISR_TXE)
    {
        //Handling Transmit Int.
    }

    /* Note that we only direct to this ISR even though we have separate 
       Int. for Tx & Rx, we have to manually check which Int. has been occured*/
}

