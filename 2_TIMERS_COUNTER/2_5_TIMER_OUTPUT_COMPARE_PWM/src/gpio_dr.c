/*file: gpio_dr.c*/

#include "rcc.h"
#include "gpio_dr.h"

/* To Initialize GPIO Pin*/
void Gpio_Init(GPIO_TypeDef *PORT, uint8_t pin, uint8_t MODE, uint8_t PUPD)
{
    PORT->MODER &= ~(3<<(pin*2));           // clear pin 
    PORT->MODER |= ((MODE)<<(pin*2));       // Set the PIN mode
    PORT->OTYPER &= ~(1<<pin);              // Default Output type - Push-Pull
    PORT->OSPEEDR |= (3<<(pin*2));          // Default set GPIO speed - HIGH
    PORT->PUPDR |= ((PUPD)<<(pin*2));       // Pull Up/Down
}

/* To set Alternate function */
void Gpio_Af(GPIO_TypeDef *PORT, uint8_t pin, uint8_t AF_NO)
{
    PORT->MODER &= ~(3<<(pin*2));           // clear pin 
    PORT->MODER |=  (2<<(pin*2));           // Alternate Function
    if(pin<=7)
    {
        PORT->AFR[0]|= (AF_NO<<(pin*4)); 
    }
    else
    {
        PORT->AFR[1]|= (AF_NO<<(pin*4)); 
    }
}

/* To set pin as Digital Output*/
/* The function expects a pointer (*PORT) to a struct (GPIO_TypeDef)*/
void Digital_Out(GPIO_TypeDef *PORT, uint8_t pin)
{
    PORT->MODER   |= (1<<(pin*2));  // Output mode
    PORT->OTYPER  &= ~(1<<pin);     // Default Push-Pull Output type 
    PORT->OSPEEDR |= (3<<(pin*2));  // Default GPIO speed - HIGH
    PORT->PUPDR   &= ~(1<<(pin*2)); // Default Pullup or Pulldown - NO here  
}

/* Write Pin level*/
void Gpio_Write(GPIO_TypeDef *PORT, uint8_t pin, uint8_t level)
{
    PORT->ODR &= ~(1<<pin);
    PORT->ODR |=  (level<<pin);
}

/* Read Pin Level*/
uint8_t Gpio_Read(GPIO_TypeDef *PORT, uint8_t pin)
{
    return PORT->IDR;
}
