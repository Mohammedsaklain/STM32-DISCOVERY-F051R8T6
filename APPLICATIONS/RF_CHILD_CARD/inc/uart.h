#include <stdint.h>

void Init_UART(void);
uint8_t receiveUART2(void);
void transmit_Char_UART2(char c);
void MSprint_Char(char *string);
void transmit_Integer(uint32_t No);
void MSprint_Integer(uint32_t *Data);