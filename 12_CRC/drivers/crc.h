#ifndef CRC_H_
#define CRC_H_

#include "custom.h" 
void CRC_Clock_Enable(void);
void CRC_Init(void);
uint32_t CRC_Calculate_32B(uint32_t Input_Data);

#endif