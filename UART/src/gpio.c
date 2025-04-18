#include "rcc.h"
#include "gpio.h"

void gpio_set(void)
{
    GPIOC->MODER   |= (1<<16) | (1<<18);  // Selecting PC8 & PC9 as OUTPUT
    GPIOC->OTYPER  &= ~(1<<8) | (1<<9);   // Push-Pull Output type 
    GPIOC->OSPEEDR |= (3<<16) | (3<<18);  // GPIO speed - HIGH
    GPIOC->PUPDR   &= ~(1<<16) | (1<<18); // Pullup or Pulldown - NO here
}