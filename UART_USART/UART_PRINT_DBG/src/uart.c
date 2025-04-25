#include "rcc.h"
#include "uart.h"

void Init_UART(void)
{
    /* Reset required bits in USART2_CR1*/
    USART2->CR1 &=~((1<<28) |           // M1
                    (1<<12) |           // M0
                    (1<<15));           // OVER Sampling by 16
    /* Set required bits in USART2_CR1*/
    USART2->CR1 |=  (USART_CR1_TE       // Enable Transmitter
                    |USART_CR1_RE       // Enable Receiver
                    |USART_CR1_UE);     // Enable UART2
    /* Reset required bits in USART2_CR2*/
    USART2->CR2 &=~ (3<<12);            //1 Stop bit

    USART2->BRR |= 69;                  // BD at 115200
}

void MSprint(char *msg, ...)    //... represents that no of arguments will be passed is unknown
{
    char buff[80];              // Temporary buffer to store data
    va_list args;               // variable of type va_list(to store no of arguments)
    va_start(args, msg);        // Pass the message & extract no of arguments
    vsprintf(buff, msg, args);  // Extracted msg is reformatted to the input msg
    for(int i=0; i< strlen(buff); i++)
    {
        USART2->TDR = buff[i];
        while(!USART2->ISR & USART_ISR_TXE);    //wait till Transmit data is Empty
    }
}
