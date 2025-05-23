#include "rcc.h"
#include "timer.h"

void Timer2_Init(void)
{
    TIM2->PSC = 0;                      // No Prescaling for Counter Frequency
    TIM2->ARR = (uint32_t)8000000;      // Timer Reload value as per 1 sec Calculation
    TIM2->CNT = 0;                      // Initial Counter Value
    TIM2->CR1 |= 1U<<0;                 // Enable Tim2 Counter
}