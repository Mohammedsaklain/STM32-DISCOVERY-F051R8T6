#include "custom.h"
#include "rcc.h"
#include "systick.h"

/*  SysTick Initialization with Delay*/
void SysTick_Init(float SysTick_Delay, uint8_t IRQ_Required){
    
    uint32_t load_val = (uint32_t)((SYSTEM_CLK/1000)*SysTick_Delay);
    __disable_irq();                        //Initially disabling the IRQs
    SysTick->CTRL = 0;                      //Initially disable Counter     (STK_CSR)
    SysTick->LOAD = (load_val - 1);         //Load value                    (STK_RVR)
    SysTick->VAL  = 0;                      //Initial Value                 (STK_CVR)
    /*(BITS: CLKSOURCE, TICKINT, ENABLE)*/
    SysTick->CTRL = 7;                      //Enable the Counter
    if(IRQ_Required==YES_IRQ){
        __enable_irq();                     //After initializing Enable IRQs
        NVIC_EnableIRQ(SysTick_IRQn);
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
/* val = (8M)/del*/
/* 8000000 = (8M)/1*/
