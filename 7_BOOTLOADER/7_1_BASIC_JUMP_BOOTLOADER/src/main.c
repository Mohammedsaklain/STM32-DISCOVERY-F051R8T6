#include "main.h"
//#include "core_cm3.h"
#include "boot.h"

void Init_Ext_Int(void);

int main()
{
	__enable_irq();
    GPIOC->MODER &= ~((3U<<18) | (3U<<16)); /*PC9, PC8*/
    GPIOC->MODER |=  ((1U<<18) | (1U<<16));
	GPIOA->MODER   &= ~(3<<0);  // PA0 has INPUT (User Button B1 connected)
    GPIOA->PUPDR &= ~(2<<0);    // Pull down in default

	Init_Ext_Int();
	while(1)
	{
	}
	return 0;
}

void Init_Ext_Int(void)
{
    SYSCFG->EXTICR[0] |= ~(0xF<<0);         // EXTO0 - PA0 Configured
    EXTI->IMR   |= 1<<0;                    // Disable mask on line0 (EXTI0)
    EXTI->FTSR &=~(1<<0);                   // Disable Falling edge trigger on line0
    EXTI->RTSR  |= 1<<0;                    // Enable Rising Edge trigger on line0

    NVIC_SetPriority(EXTI0_1_IRQn, 5);      // Set priority of EXTI0
    NVIC_EnableIRQ(EXTI0_1_IRQn);           // Enable Interrupt
}

void EXTI0_1_IRQHandler(void)
{
    if(EXTI->PR & (1<<0))   // This condition checks whether trigger has been occured (INT flag)
    {
        EXTI->PR |= 1<<0;   // Clear the interrupt flag
        GPIOC->ODR ^= ((1<<8) | (1<<9));
    }
}