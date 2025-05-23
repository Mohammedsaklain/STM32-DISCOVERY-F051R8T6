#include "rcc.h"

void rcc_clock_config(void)
{
    RCC->CR|= (1<<0);                       // Enabling HSI
    while(!(RCC->CR & (1<<1)));             // Make sure that HSI is Ready
    RCC->CFGR&=~0x3;                        // HSI Selected as System CLK

    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;     // Enable clock for I2C peripheral 
}