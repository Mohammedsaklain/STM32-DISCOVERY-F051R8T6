/*file: gpio.c*/

#include "rcc.h"
#include "gpio.h"

/* To set pin as Digital Output*/
/* The function expects a pointer (*PORT) to a struct (GPIO_TypeDef)*/
void Digital_Out(GPIO_TypeDef *PORT, uint8_t pin)
{
    PORT->MODER   |= (1<<(pin*2));  // Output mode
    PORT->OTYPER  &= ~(1<<pin);     // Push-Pull Output type 
    PORT->OSPEEDR |= (3<<(pin*2));  // GPIO speed - HIGH
    PORT->PUPDR   &= ~(1<<(pin*2)); // Pullup or Pulldown - NO here  
}

void Gpio_Write(GPIO_TypeDef *PORT, uint8_t pin, uint8_t level)
{
    PORT->ODR &= ~(1<<pin);
    PORT->ODR |=  (level<<pin);
}
