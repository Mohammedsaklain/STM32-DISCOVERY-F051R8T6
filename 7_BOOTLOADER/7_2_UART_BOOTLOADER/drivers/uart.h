#ifndef UART_H_
#define UART_H_

void UART_Init(void);
void UART_Send_Data(uint8_t data);
uint8_t UART_Receive_Data(void);
void UART_Send_String(char *string);
void MS_printf(const char *format, ...);    /* variac function */

#endif