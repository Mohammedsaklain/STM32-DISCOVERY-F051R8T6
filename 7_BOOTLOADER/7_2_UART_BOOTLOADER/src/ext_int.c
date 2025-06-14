#include "custom.h"
#include "ext_int.h"
#include "uart.h"

void External_INT_Init(void)
{
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;   // PA0
    EXTI->IMR |= EXTI_IMR_MR0;                      // Interrupt mask on line0 (EXTI0)
    EXTI->FTSR &= ~EXTI_FTSR_TR0;                   // Disable falling edge on line 0
    EXTI->RTSR |= EXTI_RTSR_TR0;                    // Enalbe rising edge on line 0 
    NVIC_EnableIRQ(EXTI0_1_IRQn);                   // Enable Interrupt
}

void External_Event_Init(void){
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;   // PA0
    EXTI->FTSR &= ~EXTI_FTSR_TR0;                   // Disable falling edge on line 0
    EXTI->RTSR |= EXTI_RTSR_TR0;                    // Enalbe rising edge on line 0 
    EXTI->EMR |= EXTI_EMR_MR0;                      // Event mask register
    EXTI->IMR &= ~(EXTI_IMR_MR0);                   // Disable Interrupt generation 
    EXTI->PR |= (EXTI_PR_PR0);                      // Clear the interrupt flag, Note: Writing 1, clears the flag
}

void EXTI0_1_IRQHandler(void)
{
    if(EXTI->PR & (1<<0))   // This condition checks whether trigger has been occured (INT flag)
    {
        EXTI->PR |= 1<<0;                // Clear the interrupt flag
        GPIOC->ODR^= ((1<<8) | (1<<9));  // Toggles an LED
    }
}