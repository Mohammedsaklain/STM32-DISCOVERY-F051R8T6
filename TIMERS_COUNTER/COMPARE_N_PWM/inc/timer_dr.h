#ifndef TIMER_DR_H_
#define TIMER_DR_H_

#define TRUE 1
#define FALSE 0

enum timer_no
{T1=1,T2,T3,T6=6,T14=14,T15,T16,T17};

enum channel_no
{CH1,CH2,CH3,CH4};

TIM_TypeDef* Get_Timer_No(uint8_t timer_no);
void Delay_uS(uint8_t timer_no, uint16_t us);
void Delay_mS(uint8_t timer_no,uint16_t ms);
void Timer_Start(uint8_t timer_no, uint8_t ENA_INT);
void Timer_Stop(uint8_t timer_no);
void Timer_Irq_Start(uint8_t timer_no);
void Timer_Irq_Stop(uint8_t timer_no);
void Timer_Compare(uint8_t timer_no, uint8_t ch_no);

#endif