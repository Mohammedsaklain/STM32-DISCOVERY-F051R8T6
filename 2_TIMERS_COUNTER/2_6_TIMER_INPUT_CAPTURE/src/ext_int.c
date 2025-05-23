#include "stm32f0xx.h"

void Init_Ext_Int(void)
{
    SYSCFG->EXTICR[0] |= ~(0xF<<0);         // EXTO0 - PA0 Configured
    EXTI->IMR   |= 1<<0;                    // Disable mask on line0 (EXTI0)
    EXTI->FTSR &=~(1<<0);                   // Disable Falling edge trigger on line0
    EXTI->RTSR  |= 1<<0;                    // Enable Rising Edge trigger on line0

    NVIC_SetPriority(EXTI0_1_IRQn, 5);      // Set priority of EXTI0
    NVIC_EnableIRQ(EXTI0_1_IRQn);           // Enable Interrupt
}

void EXTI0_1_IRQHandler (void)
{
    if(EXTI->PR & (1<<0))   // This condition checks whether trigger has been occured (INT flag)
    {
        EXTI->PR |= 1<<0;   // Clear the interrupt flag
        GPIOC->ODR^= 1<<8;  // Toggles an LED
    }
}