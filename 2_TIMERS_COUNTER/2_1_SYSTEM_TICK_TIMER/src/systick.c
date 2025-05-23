#include "stm32f0xx.h"
#include "systick.h"

void Init_SysTick(void)
{
    __disable_irq();                //Initially disabling the IRQs
    SysTick->CTRL = 0;              //Initially disable Counter     (STK_CSR)
    SysTick->LOAD = 8000000 - 1;    //Load value to get 1s delay    (STK_RVR)
    SysTick->VAL  = 0;              //Initial Value                 (STK_CVR)
    /*(BITS: CLKSOURCE, TICKINT, ENABLE)*/
    SysTick->CTRL = 7;              //Enable the Counter
    __enable_irq();                 //After initializing Enable IRQs
}

void SysTick_Handler(void)
{
    if(SysTick_CTRL_COUNTFLAG_Msk)  // Check if the COUNTFLAG is Set
    {
        GPIOC->ODR^= 1<<8;          // Toggles an LED
        SysTick->CTRL &= ~(1<<16);  // Clear the COUNTFLAG
    }
}