#include "rcc.h"
#include "gpio.h"

void gpio_set(void)
{
    GPIOB->MODER    &= ~(GPIO_MODER_MODER6 | GPIO_MODER_MODER7);       // Clear bits
    GPIOB->MODER    |=  (GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1);   // Alternate function for PB6(SCL) & PB7(SDA)
    GPIOB->OSPEEDR  |=  (GPIO_OSPEEDER_OSPEEDR6 | GPIO_OSPEEDER_OSPEEDR7);//High speed 
    GPIOB->OTYPER   |=  (GPIO_OTYPER_OT_6 | GPIO_OTYPER_OT_7);         // Open-Drain for PB6 & PB7
    GPIOB->PUPDR    |=  (GPIO_PUPDR_PUPDR6_0 | GPIO_PUPDR_PUPDR7_0);   // Pull - up
    GPIOB->AFR[0]   |=  ((1<<24) | (1<<28));                           // AF1 selection at 26 & 28
}