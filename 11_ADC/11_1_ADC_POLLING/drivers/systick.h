#ifndef SYSTICK_H_
#define SYSTICK_H_

void SysTick_Init(float SysTick_Delay,uint8_t IRQ_Required);
enum SYSTICK_IRQ_REQ{
    NO_IRQ  =0,
    YES_IRQ =1,
};
#endif