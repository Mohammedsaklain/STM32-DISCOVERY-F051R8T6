/*  file: STM32_bootloader.c 
    Date: 21/05/25*/

#include "main.h"      
#include "boot.h"
#include "stm32f0xx.h"

extern unsigned long _stack_end; // Bootloader's stack end (for its own initial SP)
extern unsigned long _data_flash;
extern unsigned long _data_begin;
extern unsigned long _data_end;
extern unsigned long _bss_end;
extern unsigned long _bss_begin;

// Function prototypes
void handler_default(void);
void handler_reset(void);
static void bootloader_main(void); // Declared static as it's not exposed
bool application_valid(void);


/* Default handler for unused interrupts*/
void handler_default(void){
    while(1);
}

/* First function executed after reset (Bootloader's entry point)*/
void handler_reset(void){
    unsigned long *source;
    unsigned long *destination;

    // --- Bootloader's Initial RAM Setup ---
    // 1. Copy .data section from Flash to RAM
    source = &_data_flash;
    for(destination = &_data_begin; destination < &_data_end;)
        *(destination++) = *(source++);

    // 2. Zero-fill .bss section in RAM
    for(destination = &_bss_begin; destination < &_bss_end;)
        *(destination++) = 0;

    // 3. Enable SYSCFG clock (CRITICAL for memory remapping)
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    __DSB(); // Data Synchronization Barrier
    __ISB(); // Instruction Synchronization Barrier

    // 4. Copy Bootloader's Vector Table from Flash (0x08000000) to RAM (0x20000000)
    // The bootloader's vector table is initially linked at 0x08000000
    volatile uint32_t *boot_flash_vec_table = (volatile uint32_t*)0x08000000;
    volatile uint32_t *ram_vec_table_ptr = (volatile uint32_t*)RAM_VECTOR_TABLE_ADDR;

    for (int i = 0; i < VECTOR_TABLE_SIZE_WORDS; i++) {
        ram_vec_table_ptr[i] = boot_flash_vec_table[i];
    }

    // 5. Remap SRAM to address 0x00000000 using SYSCFG_CFGR1.MEM_MODE
    SYSCFG->CFGR1 &= ~(3<<0); // Clear MEM_MODE bits (0b11)
    SYSCFG->CFGR1 |= (2<<0);  // Set MEM_MODE to SRAM (0b10)

    // Ensure memory operations and remapping are complete before any other code
    __DSB();
    __ISB();

    // Now, the system will fetch its vector table from RAM_VECTOR_TABLE_ADDR (0x20000000)
    // Any interrupts from here on will use the RAM-based bootloader table.

    rcc_clock_config();

    // Configure PA0 as input with pull-down for boot pin check
    GPIOA->MODER &= ~(3U<<0); // Clear PA0 mode bits (set to input)
    GPIOA->PUPDR |= (2U<<0);  // Set PA0 to pull-down (0b10)

    if((GPIOA->IDR & (1U<<0)) == (1U<<0)){
        /* Bootloader pin is high, so enter into bootmode with bootloader_main fun.*/
        bootloader_main(); // This function will execute the bootloader's primary logic
    }else{
        /* Boot pin is not active, prepare to jump to application */
        __disable_irq(); // Disable interrupts during the jump process

        // The vector table is currently in RAM (0x20000000) and contains bootloader's handlers.
        // We need to OVERWRITE it with the application's vector table.

        // Copy Application's Vector Table from Flash (APPLICATION_START_ADDR) to RAM (RAM_VECTOR_TABLE_ADDR)
        volatile uint32_t *app_flash_vec_table = (volatile uint32_t*)APPLICATION_START_ADDR;
        // ram_vec_table_ptr is already pointing to RAM_VECTOR_TABLE_ADDR (0x20000000)
        for (int i = 0; i < VECTOR_TABLE_SIZE_WORDS; i++) {
            ram_vec_table_ptr[i] = app_flash_vec_table[i];
        }

        // Ensure the vector table copy is complete and visible to the CPU
        __DSB();
        __ISB();

        // Perform basic validation of the application firmware
        if(!application_valid()){
            // If the application is not valid, enter an infinite error loop
            // Ensure GPIOC clock is enabled if blinking LED, and set mode
            RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
            GPIOC->MODER &= ~(3U<<18); /*PC9 - LED for Boot code*/
            GPIOC->MODER |=  (1U<<18);
            while(1){
                for(volatile int i=0;i<8000;i++){}
                GPIOC->ODR ^= (1U<<9); // Blink if no valid app
            }
        }

        // --- Application Jump ---
        // The stack pointer (MSP) needs to be set for the application *before* jumping.
        // Get the application's initial SP from its vector table in RAM.
        uint32_t app_msp = *(volatile uint32_t*)RAM_VECTOR_TABLE_ADDR;
        __set_MSP(app_msp); // CRITICAL: Set application's stack pointer

        // Get Application Reset Handler address from its vector table in RAM.
        uint32_t reset_handler_address = *(volatile uint32_t*)(RAM_VECTOR_TABLE_ADDR + 4);

        // Cast to function pointer and execute (LSB must be 1 for Thumb mode)
        typedef void (*pFunction)(void);
        pFunction jump_to_app = (pFunction)(reset_handler_address | 0x1);
        jump_to_app();      /* The actual jump, means Program counter is loaded with reset_handler_address( of application)*/
    }
    while(1); /* Should never come here */
}

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

__attribute__ ((section(".interrupt_vector")))
void (* const table_interrupt_vector[])(void) =
{
    // This table is the *initial* vector table linked into Flash (0x08000000).
    // It will be copied to RAM early in handler_reset for active use.
    (void *)&_stack_end,      // 0: Top of stack for the bootloader
    handler_reset,            // 1: Reset Handler
    NMI_Handler,              // 2: NMI Handler
    HardFault_Handler,        // 3: Hard Fault Handler
    0, 0, 0, 0, 0, 0, 0,       // Reserved
    SVC_Handler,              // 11: SVC Handler
    0, 0,                     // Reserved
    PendSV_Handler,           // 14: PendSV Handler
    SysTick_Handler,          // 15: SysTick Handler
    // External interrupts (ensure these are in correct order for your device)
    WWDG_IRQHandler,          // 16
    PVD_IRQHandler,           // 17
    RTC_IRQHandler,           // 18
    FLASH_IRQHandler,         // 19
    RCC_IRQHandler,           // 20
    EXTI0_1_IRQHandler,       // 21
    EXTI2_3_IRQHandler,       // 22
    EXTI4_15_IRQHandler,      // 23
    TS_IRQHandler,            // 24
    DMA1_Channel1_IRQHandler, // 25
    DMA1_Channel2_3_IRQHandler,// 26
    DMA1_Channel4_5_IRQHandler,// 27
    ADC1_COMP_IRQHandler,     // 28
    TIM1_BRK_UP_TRG_COM_IRQHandler,// 29
    TIM1_CC_IRQHandler,       // 30
    TIM2_IRQHandler,          // 31
    TIM3_IRQHandler,          // 32
    TIM6_DAC_IRQHandler,      // 33
    0,                        // 34: Reserved
    TIM14_IRQHandler,         // 35
    TIM15_IRQHandler,         // 36
    TIM16_IRQHandler,         // 37
    TIM17_IRQHandler,         // 38
    I2C1_IRQHandler,          // 39
    I2C2_IRQHandler,          // 40
    SPI1_IRQHandler,          // 41
    SPI2_IRQHandler,          // 42
    USART1_IRQHandler,        // 43
    USART2_IRQHandler,        // 44
    0,                        // 45: Reserved
    CEC_IRQHandler,           // 46: CEC_CAN_IRQHandler (renamed from CEC for clarity)
    0                         // 47: Reserved
};


// --- Bootloader_main() function  ---
static void bootloader_main(void)
{
    // The bootloader's vector table is already in RAM at 0x20000000.
    // Any interrupts that fire while in bootloader_main will use this RAM table.

    GPIOC->MODER &= ~(3U<<18); /*PC9 - LED for Boot code*/
    GPIOC->MODER |=  (1U<<18); // Set PC9 to General purpose output mode

    /* LED blinks inorder to indicate controller entered boot mode*/
    for(uint8_t i=0;i<5;i++)
    {
        GPIOC->ODR ^= (1U<<9); // PC9
        for(volatile int i=0;i<80000;i++){}
    }

    // If application needs to be updated, this is where you'd handle it.
    // For now, it checks if the application is valid and jumps if so.
    // If you want the bootloader to stay here, remove the jump logic below
    // and replace with a loop or specific bootloader tasks.

    if(application_valid()){
        // If application is valid, jump to it (after bootloader specific tasks are done)
        __disable_irq(); // Disable interrupts before jumping

        // Re-copy Application's Vector Table from Flash to RAM (redundant if already done in handler_reset, but safe)
        volatile uint32_t *app_flash_vec_table = (volatile uint32_t*)APPLICATION_START_ADDR;
        volatile uint32_t *ram_vec_table_ptr_local = (volatile uint32_t*)RAM_VECTOR_TABLE_ADDR;
        for (int i = 0; i < VECTOR_TABLE_SIZE_WORDS; i++) {
            ram_vec_table_ptr_local[i] = app_flash_vec_table[i];
        }

        __DSB();
        __ISB();

        uint32_t app_msp = *(volatile uint32_t*)RAM_VECTOR_TABLE_ADDR;
        __set_MSP(app_msp);

        uint32_t reset_handler_address = *(volatile uint32_t*)(RAM_VECTOR_TABLE_ADDR + 4);

        typedef void (*pFunction)(void);
        pFunction jump_to_app = (pFunction)(reset_handler_address | 0x1);
        jump_to_app();
    }

    // If application_valid fails, or if bootloader_main is meant to be
    // an infinite loop for "bootloader active" mode:
    while(1){
        /* If no valid application or staying in bootloader mode,
           enter into infinite loop while onboard led blinks */
        for(volatile int i=0;i<80000;i++){}
        GPIOC->ODR ^= (1U<<8); // This should also be PC8 (1U<<8) for blinking LED
    }
}

bool application_valid(void)
{
    uint32_t app_msp = *(volatile uint32_t*)APPLICATION_START_ADDR;       /* stack pointer*/
    uint32_t app_reset_handler = *(volatile uint32_t*)(APPLICATION_START_ADDR + 4); /* reset handler*/

    // Basic checks:
    // 1. MSP should point within RAM limits
    if (app_msp < RAM_BASE || app_msp > (RAM_BASE + RAM_SIZE)) {
        return false;
    }
    // 2. Reset Handler address should point within application Flash limits
    // And ensure LSB is 1 for Thumb mode
    if ((app_reset_handler < APPLICATION_START_ADDR) ||
        (app_reset_handler >= (APPLICATION_START_ADDR + 48U * 1024U)) ||
        ((app_reset_handler & 0x1) == 0)) { // Check if LSB is 0 (should be 1 for Thumb)
        return false;
    }
    return true;
}