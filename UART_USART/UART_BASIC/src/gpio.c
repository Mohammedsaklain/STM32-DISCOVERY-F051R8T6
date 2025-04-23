#include "rcc.h"
#include "gpio.h"

void gpio_set(void)
{   
    GPIOA->MODER &= ~((3<<4) | (3<<6));     // Clear bits
    GPIOA->MODER |= (2<<4) | (2<<6);        // Selecting PA2(TX) & PA3(RX) as alternate function
    GPIOA->AFR[0] &= ~((1<<8) | (1<<12));   // Clear Bits
    GPIOA->AFR[0] |= (1<<8) | (1<<12);      // Alternate function register - AF1 for PA2 & PA3
}