#include "custom.h"
#include "rcc.h"
#include "systick.h"

#ifdef SYSTICK_REQ
/*  SysTick Initialization with Delay*/
void SysTick_Init(float SysTick_Delay,uint8_t IRQ_Required){
    float Load_Val=0;
    Load_Val = (float)SYSTEM_CLK * SysTick_Delay;
    __disable_irq();                        //Initially disabling the IRQs
    SysTick->CTRL = 0;                      //Initially disable Counter     (STK_CSR)
    SysTick->LOAD = (int)(Load_Val - 1);      //Load value to get 1s delay    (STK_RVR)
    SysTick->VAL  = 0;                      //Initial Value                 (STK_CVR)
    /*(BITS: CLKSOURCE, TICKINT, ENABLE)*/
    SysTick->CTRL = 7;                      //Enable the Counter
    if(IRQ_Required==YES_IRQ){
        __enable_irq();                         //After initializing Enable IRQs
    }
    else{
        while(!((SysTick->CTRL) & (SysTick_CTRL_COUNTFLAG_Msk)));    // Returns 1 if timer counted to 0 
    }
    
}

void SysTick_Handler(void){
    if(SysTick_CTRL_COUNTFLAG_Msk){  // Check if the COUNTFLAG is Set
        SysTick->CTRL &= ~(1<<16);   // Clear the COUNTFLAG
        GPIOC->ODR^= (1<<8);
    }
}

/* del = (8M)/val */
/* 8000000 = (8M)/1*/

#endif