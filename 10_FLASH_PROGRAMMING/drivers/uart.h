#include "main.h"

void UART_Init(void);
void UART_Send_Data(uint8_t data);
unsigned char UART_Receive_Data(void);
void UART_Send_String(char *string);

void MS_printf(const char *format, ...);    /* variac function */