#include "rcc.h"
#include "gpio.h"

void gpio_set(void)
{
    GPIOC->MODER   |= (1<<16);  // Selecting PC8 as an OUTPUT
    GPIOC->OTYPER  &= ~(1<<8);  // Push-Pull Output type 
    GPIOC->OSPEEDR |= (3<<16);  // GPIO speed - HIGH
    GPIOC->PUPDR   &= ~(1<<16); // Pullup or Pulldown - NO here

    GPIOA->MODER   &= ~(3<<0);  // PA0 has INPUT
}