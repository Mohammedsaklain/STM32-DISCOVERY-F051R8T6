#include "main.h"
#include "boot.h"

extern unsigned long _data_flash;
extern unsigned long _data_begin;
extern unsigned long _data_end;
extern unsigned long _bss_begin;
extern unsigned long _bss_end;
extern unsigned long _stack_end;

void handler_default(void)
{
    while (1)
    {}
}
void handler_reset(void){
    unsigned long *source;
    unsigned long *destination;

    source = &_data_flash;
    for(destination = &_data_begin; destination < &_data_end;)
        *(destination++) = *(source++);
    
    for(destination = &_bss_begin; destination < &_bss_end;)
        *(destination++) = 0;
    
    rcc_clock_config();
    #ifdef HOST_UNIT_TEST
        origin(); // Since we can't call main for Unity framework, instead call origin 
    #else
        main();
    #endif
}

// Function prototypes
void handler_reset(void);
void handler_default(void) __attribute__((weak));

// Exception and Interrupt Handler prototypes (weakly defined)
void NMI_Handler(void) __attribute__((weak, alias("handler_default")));
void HardFault_Handler(void) __attribute__((weak, alias("handler_default")));
void SVC_Handler(void) __attribute__((weak, alias("handler_default")));
void PendSV_Handler(void) __attribute__((weak, alias("handler_default")));
void SysTick_Handler(void) __attribute__((weak, alias("handler_default")));
void WWDG_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void PVD_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void RTC_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void FLASH_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void RCC_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void EXTI0_1_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void EXTI2_3_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void EXTI4_15_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void TS_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void DMA1_Channel1_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void DMA1_Channel2_3_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void DMA1_Channel4_5_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void ADC1_COMP_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void TIM1_BRK_UP_TRG_COM_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void TIM1_CC_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void TIM2_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void TIM3_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void TIM6_DAC_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void TIM14_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void TIM15_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void TIM16_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void TIM17_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void I2C1_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void I2C2_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void SPI2_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void USART1_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void USART2_IRQHandler(void) __attribute__((weak, alias("handler_default")));
void CEC_IRQHandler(void) __attribute__((weak, alias("handler_default")));

__attribute__ ((section(".interrupt_vector")))
void (* const table_interrupt_vector[])(void) =
{
    (void *) &_stack_end,      // 0: Top of stack
    handler_reset,             // 1: Reset Handler
    NMI_Handler,               // 2: NMI Handler
    HardFault_Handler,         // 3: Hard Fault Handler
    0,                         // 4: Reserved
    0,                         // 5: Reserved
    0,                         // 6: Reserved
    0,                         // 7: Reserved
    0,                         // 8: Reserved
    0,                         // 9: Reserved
    0,                         // 10: Reserved
    SVC_Handler,               // 11: SVC Handler
    0,                         // 12: Reserved
    0,                         // 13: Reserved
    PendSV_Handler,            // 14: PendSV Handler
    SysTick_Handler,           // 15: SysTick Handler
    WWDG_IRQHandler,           // 16: WWDG_IRQHandler
    PVD_IRQHandler,            // 17: PVD_IRQHandler
    RTC_IRQHandler,            // 18: RTC_IRQHandler
    FLASH_IRQHandler,          // 19: FLASH_IRQHandler
    RCC_IRQHandler,            // 20: RCC_CRS_IRQHandler
    EXTI0_1_IRQHandler,        // 21: EXTI0_1_IRQHandler
    EXTI2_3_IRQHandler,        // 22: EXTI2_3_IRQHandler
    EXTI4_15_IRQHandler,       // 23: EXTI4_15_IRQHandler
    TS_IRQHandler,             // 24: TSC_IRQHandler
    DMA1_Channel1_IRQHandler,  // 25: DMA1_Channel1_IRQHandler
    DMA1_Channel2_3_IRQHandler,// 26: DMA1_Channel2_3_IRQHandler
    DMA1_Channel4_5_IRQHandler,// 27: DMA1_Channel4_5_IRQHandler
    ADC1_COMP_IRQHandler,      // 28: ADC1_COMP_IRQHandler
    TIM1_BRK_UP_TRG_COM_IRQHandler,// 29: TIM1_BRK_UP_TRG_COM_IRQHandler
    TIM1_CC_IRQHandler,        // 30: TIM1_CC_IRQHandler
    TIM2_IRQHandler,           // 31: TIM2_IRQHandler
    TIM3_IRQHandler,           // 32: TIM3_IRQHandler
    TIM6_DAC_IRQHandler,       // 33: TIM6_DAC_IRQHandler
    0,                         // 34: Reserved
    TIM14_IRQHandler,          // 35: TIM14_IRQHandler
    TIM15_IRQHandler,          // 36: TIM15_IRQHandler
    TIM16_IRQHandler,          // 37: TIM16_IRQHandler
    TIM17_IRQHandler,          // 38: TIM17_IRQHandler
    I2C1_IRQHandler,           // 39: I2C1_IRQHandler
    I2C2_IRQHandler,           // 40: I2C2_IRQHandler
    SPI1_IRQHandler,           // 41: SPI1_IRQHandler
    SPI2_IRQHandler,           // 42: SPI2_IRQHandler
    USART1_IRQHandler,         // 43: USART1_IRQHandler
    USART2_IRQHandler,         // 44: USART2_IRQHandler
    0,                         // 45: Reserved
    CEC_IRQHandler,            // 46: CEC_CAN_IRQHandler
    0                          // 47: Reserved
};