#ifndef UART_H_
#define UART_H_

#include "stdint.h"
void UART_Init(void);
void UART_Send_Data(uint8_t data);
//uint8_t UART_Receive_Data(void);
//void UART_Send_String(char *string);
void print_float(float Num);
void MS_printf(const char *format, ...);    /* variac function */

#endif