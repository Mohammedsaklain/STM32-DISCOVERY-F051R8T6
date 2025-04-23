#include "rcc.h"
#include "timer.h"

void Timer6_Init(void)
{
    /* Clock to the TIM6 is same as for the APB bus(8MHz)*/
    TIM6->PSC = (8-1);  //(-1 bcz 1 PSC+1)// Prescaling by 8, 8MHz/8 = 1MHz => gives to 1uS
    TIM6->ARR = 0xFFFF;                 // Given Max Timer Reload value
    //TIM6->CNT = 0;                      // Initial Counter Value
    TIM6->CR1 |= 1U<<0;                 // Enable Tim6 Counter
    while(!TIM6->SR & (1<<0));          // Set by hardware when the registers are updated
}

void Delay_uS(uint16_t us)
{
    TIM6->CNT = 0;                  // First reset the count
    while(TIM6->CNT <us);           // Wait till desired count value reached
}

void Delay_mS(uint16_t ms)
{
    for(uint16_t i=0;i<ms;i++)
    {
        Delay_uS(1000);             // Delay for 1ms
    }
}