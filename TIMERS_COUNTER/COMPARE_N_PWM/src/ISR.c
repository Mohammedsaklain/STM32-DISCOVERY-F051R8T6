#include "rcc.h"
#include "timer_dr.h"
#include "stm32f0xx.h"
#include "gpio_dr.h"

/* ISR for Timer - 1 */
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
    if(TIM1->SR & TIM_SR_UIF)             // Check first whether INT flag occured
    {
        TIM1->SR &= ~(TIM_SR_UIF);        // Clear the Interrupt Flag
        GPIOC->ODR^= (1<<8);
    }
}

/* ISR for Timer - 2 */
void TIM2_IRQHandler(void)
{
 
}

/* ISR for Timer - 3 */
void TIM3_IRQHandler(void)
{
 
}

/* ISR for Timer - 6 */
void TIM6_DAC_IRQHandler(void)
{
 
}

/* ISR for Timer - 14 */
void TIM14_IRQHandler(void)
{

}

/* ISR for Timer - 15 */
void TIM15_IRQHandler(void)
{

}

/* ISR for Timer - 16 */
void TIM16_IRQHandler(void)
{
 
}

/* ISR for Timer - 17 */
void TIM17_IRQHandler(void)
{

}