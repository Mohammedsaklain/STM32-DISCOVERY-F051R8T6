#include "rcc.h"
#include "timer_dr.h"
#include "stm32f0xx.h"
#include "gpio_dr.h"

TIM_TypeDef* Get_Timer_No(uint8_t timer_no)
{
    TIM_TypeDef * TIMER; 
    switch(timer_no)
    {
        case T1:     TIMER = TIM1;break;
        case T2:     TIMER = TIM2;break;
        case T3:     TIMER = TIM3;break;
        case T6:     TIMER = TIM6;break;
        case T14:    TIMER = TIM14;break;
        case T15:    TIMER = TIM15;break;
        case T16:    TIMER = TIM16;break;
        case T17:    TIMER = TIM17;break;
    }
    return TIMER;
}

/* TO initialize Timer: 
Arguments : timer_no = TIM2 - Timer Number
            INT      = TRUE - Enables the Interrupt*/
void Timer_Default_Start(uint8_t timer_no, uint8_t ENA_INT)
{
    /* When we need Interrupt based Timer Operation*/
    /* ((1k(ARR) x 8k(PSC))/8M(TMR_FRQ))=1Sec */
    TIM_TypeDef * TIMER = Get_Timer_No(timer_no);
    if(ENA_INT==TRUE)
    {
        TIMER->PSC = 7999;                      // Prescaling by 8000, 8MHz/8000 = 1KHz => gives us to 1mS
        TIMER->ARR = 1000;                      // Timer Reload value based on Calculation 
        TIMER->CNT = 0;                         // Reset the count
        TIMER->CR1 |= TIM_CR1_CEN;              // Enable Tim Counter
        TIMER->DIER |= TIM_DIER_UIE;            // Enable the Timer Interrupt
        Timer_Irq_Start(timer_no);   
    }
            
    /* Default, 1uS*/
    else
    {
        TIMER->PSC = 7;                      // Prescaling by 8, 8MHz/8 = 1uSec
        TIMER->ARR = 0xFFFF;                 // Timer Reload value - Max
        TIMER->CNT = 0;                      // Reset the count
        TIMER->DIER &= ~TIM_DIER_UIE;        // Disable the Timer Interrupt
        TIMER->CR1 |= TIM_CR1_CEN;           // Enable Tim Counter
        while(!TIMER->SR & TIM_SR_UIF); 
    }
}

/* Custom Initialization of Timer*/
void Timer_Init(uint8_t timer_no, uint16_t prescaler, uint32_t auto_reload, uint8_t ENA_INT)
{
    TIM_TypeDef * TIMER = Get_Timer_No(timer_no);
    if(ENA_INT==TRUE)
    {
        /* When we need Interrupt based Timer Operation*/
        TIMER->PSC = prescaler;                 // Prescaling by 8000, 8MHz/8000 = 1KHz => gives us to 1mS
        TIMER->ARR = auto_reload;               // Timer Reload value based on Calculation 
        TIMER->CNT = 0;                         // Reset the count
        TIMER->CR1 |= TIM_CR1_CEN;              // Enable Tim Counter
        TIMER->DIER |= TIM_DIER_UIE;            // Enable the Timer Interrupt  
    }
    else
    {
         /* When we need Interrupt based Timer Operation*/
         TIMER->PSC = prescaler;                 // Prescaling by 8000, 8MHz/8000 = 1KHz => gives us to 1mS
         TIMER->ARR = auto_reload;               // Timer Reload value based on Calculation 
         TIMER->CNT = 0;                         // Reset the count
         TIMER->CR1 |= TIM_CR1_CEN;              // Enable Tim Counter
         TIMER->DIER &= ~TIM_DIER_UIE;           // Disable the Timer Interrupt
    }
}

/* Delay in Micro Seconds*/
void Delay_uS(uint8_t timer_no, uint16_t us)
{
    TIM_TypeDef * TIMER = Get_Timer_No(timer_no);
    TIMER->CNT=0;
    while(TIMER->CNT <us);           // Wait till desired count value reached
}

/* Delay in milli Seconds*/
void Delay_mS(uint8_t timer_no,uint16_t ms)
{
    for(uint16_t i=0;i<ms;i++)
    {
        Delay_uS(timer_no,1000);             // Delay for 1ms
    }
}

/* To stop Timer*/
void Timer_Stop(uint8_t timer_no)
{
    TIM_TypeDef * TIMER = Get_Timer_No(timer_no);
    TIMER->CR1 &= ~(TIM_CR1_CEN);            // Disable the timer
}

/* To enable the Timer Interrupt */
void Timer_Irq_Start(uint8_t timer_no)
{
    __disable_irq();
    switch(timer_no)
    {
        case T1:     NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);break;
        case T2:     NVIC_EnableIRQ(TIM2_IRQn);break;
        case T3:     NVIC_EnableIRQ(TIM3_IRQn);break;
        case T6:     NVIC_EnableIRQ(TIM6_DAC_IRQn);break;
        case T14:    NVIC_EnableIRQ(TIM14_IRQn);break;
        case T15:    NVIC_EnableIRQ(TIM15_IRQn);break;
        case T16:    NVIC_EnableIRQ(TIM16_IRQn);break;
        case T17:    NVIC_EnableIRQ(TIM17_IRQn);break;
    }
    __enable_irq();
}

/* To Disable the Timer Interrupt */
void Timer_Irq_Stop(uint8_t timer_no)
{
    TIM_TypeDef * TIMER = Get_Timer_No(timer_no);
    TIMER->DIER &= ~(TIM_DIER_UIE);       //Disable the Interrupt
    __disable_irq();
    switch(timer_no)
    {
        case T1:     NVIC_DisableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);break;
        case T2:     NVIC_DisableIRQ(TIM2_IRQn);break;
        case T3:     NVIC_DisableIRQ(TIM3_IRQn);break;
        case T6:     NVIC_DisableIRQ(TIM6_DAC_IRQn);break;
        case T14:    NVIC_DisableIRQ(TIM14_IRQn);break;
        case T15:    NVIC_DisableIRQ(TIM15_IRQn);break;
        case T16:    NVIC_DisableIRQ(TIM16_IRQn);break;
        case T17:    NVIC_DisableIRQ(TIM17_IRQn);break;
    }
    __enable_irq();                       // Turnig On, inorder to prevent other IRQ's to be stopped
}

/* To enable Timer Compare Function
arguments: timer_no - TIM3, ch_no - CH1*/
void Timer_Compare_Init(uint8_t timer_no, uint8_t ch_no, uint8_t lag_degree)
{
    uint32_t TMARR;
    TIM_TypeDef * TIMER = Get_Timer_No(timer_no);
    TMARR = TIMER->ARR;
    TIMER->CCMR1 |= (0x3030);           // Toggle-OC1REF toggles when TIMx_CNT=TIMx_CCR1
    TIMER->CCER  |=  (1<<(ch_no*4));    // Channel Selection 
    TIMER->BDTR  |= 0x8000;             // MOE
    switch(ch_no)
    {   /* CCRx - Calculation */
        case 0:TIMER->CCR1  |= TMARR;break;
        case 1:TIMER->CCR2  |= ((TMARR * lag_degree)/100);break;
        case 2:TIMER->CCR3  |= ((TMARR * lag_degree)/100);break;
        case 3:TIMER->CCR4  |= ((TMARR * lag_degree)/100);break;
    }
    TIMER->CR1   |= TIM_CR1_CEN;        // Counter Enable
}

void Timer_PWM_Init(uint8_t timer_no, uint8_t ch_no, uint8_t Duty_Cycle)
{
    uint32_t TMARR;
    TIM_TypeDef * TIMER = Get_Timer_No(timer_no);
    TMARR = TIMER->ARR;
    TIMER->CCMR1 |= 0x6060;             // PWM mode
    TIMER->CCER  |= (1<<(ch_no*4));     // Channel Selection 
    TIMER->BDTR  |= 0x8000;             // MOE
    switch(ch_no)
    {   /* CCRx - Calculation to get desired PWM Duty cycle*/
        case 0:TIMER->CCR1  |= ((TMARR * Duty_Cycle)/100);break;
        case 1:TIMER->CCR2  |= ((TMARR * Duty_Cycle)/100);break;
        case 2:TIMER->CCR3  |= ((TMARR * Duty_Cycle)/100);break;
        case 3:TIMER->CCR4  |= ((TMARR * Duty_Cycle)/100);break;
    }
    TIMER->EGR |= TIM_EGR_UG;
	TIMER->CR1 |= TIM_CR1_CEN; 
}
