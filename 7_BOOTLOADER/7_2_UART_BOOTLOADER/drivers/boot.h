#ifndef BOOT_H_
#define BOOT_H_
    
#define APPLICATION_START_ADDR  0x08004000UL
#define RAM_BASE                0x20000000UL
#define RAM_SIZE                0x00002000UL
#define RAM_VECTOR_TABLE_ADDR   (RAM_BASE)                      // Define the RAM location for the vector table
    
/* Boot Flash Storage area, total of 44KB size*/
#define BOOT_FLASH_NUM_PAGES        (11U)
#define VECTOR_TABLE_SIZE_WORDS (16 + 32)                       // size of the vector table (16 core + 32 external IRQs for STM32F0)
#define VECTOR_TABLE_SIZE_BYTES (VECTOR_TABLE_SIZE_WORDS * 4)   // 192 bytes
    
#define MAX_PACKET_DATA_SIZE 20
#define ACK  0xCC
#define NACK 0xEE

enum boot_uart_commands{
    START_BYTE  =  0x01,
    END_BYTE    =  0x02,
    ERASE       =  0x03,
    WRITE       =  0x04,
    JUMP        =  0x05,
    READY       =  0x06,
};

extern unsigned long _stack_end; // Bootloader's stack end (for its own initial SP)
extern unsigned long _data_flash;
extern unsigned long _data_begin;
extern unsigned long _data_end;
extern unsigned long _bss_end;
extern unsigned long _bss_begin;

// Function prototypes
void handler_default(void);
void handler_reset(void);
bool application_valid(void);
uint8_t Calculated_Checksum(const uint8_t *Data, uint8_t Length);


// Exception and Interrupt Handler prototypes (weakly defined)
// These are the bootloader's handlers. They will be in Flash, but the
// RAM vector table will point to them after the initial copy.
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

#endif
