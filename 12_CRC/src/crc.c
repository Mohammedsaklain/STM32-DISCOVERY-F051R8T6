#include "crc.h"
#include "custom.h"

void CRC_Clock_Enable(void){
    RCC->AHBENR |= RCC_AHBENR_CRCEN;    /* Enable Clock for CRC Unit */
}

void CRC_Init(void){
    CRC_Clock_Enable();
    CRC->CR |= CRC_CR_RESET;            /* Resets the CRC Unit */
}

uint32_t CRC_Calculate_32B(uint32_t Input_Data){
    CRC->CR |= CRC_CR_RESET;            /* Resets the CRC Unit */
    CRC->DR = Input_Data;               /* Load the Input data(which is a dividend, polynomial is a divisor)*/
    return (CRC->DR);                   /* Same register when read, returns the Output */
}