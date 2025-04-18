#include "rcc.h"

void rcc_clock_config(void)
{
    RCC->CR|= (1<<0);               // Enabling HSI
    while(!(RCC->CR & (1<<1)));     // Make sure that HSI is Ready
    RCC->CFGR&=~0x3;                // HSI Selected as System CLK

    RCC->AHBENR |= 1<<19;           // Enable clock for IO Port C
}