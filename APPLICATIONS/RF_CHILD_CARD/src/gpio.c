#include "rcc.h"
#include "gpio.h"

void gpio_set(void)
{   
    GPIOA->MODER &= ~((3<<4) | (3<<6));     // Clear bits
    GPIOA->MODER |= (2<<4) | (2<<6);        // Selecting PA2(TX) & PA3(RX) as alternate function
    GPIOA->AFR[0] &= ~((1<<8) | (1<<12));   // Clear Bits
    GPIOA->AFR[0] |= (1<<8) | (1<<12);      // Alternate function register - AF1 for PA2 & PA3

    GPIOC->MODER &= ~((3<<16) | (3<<18) | (3<<20));      // Clear PC8, PC9 & PC10(As input)
    GPIOC->MODER |=  (1<<16)  | (1<<18);                 // Set PC8, PC9 as OUTPUT
    GPIOC->OSPEEDR |= (3<<16) | (3<<18) | (3<<20);       // High speed mode
}