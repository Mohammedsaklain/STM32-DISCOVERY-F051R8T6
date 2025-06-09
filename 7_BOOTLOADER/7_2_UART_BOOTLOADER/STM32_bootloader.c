/*  file: STM32_bootloader.c 
    Date: 21/05/25*/

#include "custom.h"
#include "rcc.h"
#include "boot.h"
#include "uart.h"
#include "flash.h"

static void bootloader_main(void); // Declared static as it's not exposed

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

    rcc_clock_config();

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

    // Configure PA0 as input with pull-down for boot pin check
    GPIOA->MODER &= ~(3U<<0); // Clear PA0 mode bits (set to input)
    GPIOA->PUPDR |= (2U<<0);  // Set PA0 to pull-down (0b10)
    GPIOC->MODER &= ~((3U<<18) | (3U<<16));  /*PC9, PC8 - LED for Boot code*/
    GPIOC->MODER |=  ((1U<<18) | (1U<<16));  // Set PC9, PC8 to General purpose output mode

    // 6. Check wether BOOT pin pressed, if Yes Enter BOOTLOADER
    if((GPIOA->IDR & (1U<<0)) == 1){
        /* Bootloader pin is high, so enter into bootmode with bootloader_main fun.*/
        bootloader_main(); // This function will execute the bootloader's primary logic
    }
    /* If BOOT pin not pressed, then jump to existing app code*/
    else{
        /* Boot pin is not active, prepare to jump to application */
        __disable_irq(); // Disable interrupts during the jump process

        /* Disable SysTick counter, interrupt, and clock source*/
        SysTick->CTRL = 0;
        SysTick->LOAD = 0;
        SysTick->VAL  = 0;

        /* Reset UART2 Peripheral before Jump */
        RCC->APB1RSTR |= RCC_APB1RSTR_USART2RST;
        RCC->APB1RSTR &= ~RCC_APB1RSTR_USART2RST;
        /* Reset GPIO's */
        RCC->AHBRSTR |= RCC_AHBRSTR_GPIOARST; // Reset GPIOA
        RCC->AHBRSTR &= ~RCC_AHBRSTR_GPIOARST;
        RCC->AHBRSTR |= RCC_AHBRSTR_GPIOCRST; // Reset GPIOC
        RCC->AHBRSTR &= ~RCC_AHBRSTR_GPIOCRST;

        /* Clear all pending interrupt flags in NVIC */
        for(uint8_t i = 0; i < 32; i++) {
            NVIC->ICER[i >> 5] = (1UL << (i & 0x1F)); // Disable interrupt
            NVIC->ICPR[i >> 5] = (1UL << (i & 0x1F)); // Clear pending flag
        }
        // Also clear any pending System Handler Control and State Register (SHCSR) faults if desired
        SCB->SHCSR = 0;
        __DSB();
        __ISB();

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
            while(1){
                GPIOC->ODR ^= (1U<<9); // Blink if no valid app
                for(volatile int i=0;i<80000;i++);
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

    UART_Init(); // Initialize UART to receive .bin file

    /* LED blinks inorder to indicate controller entered boot mode*/
    for(uint8_t i=0;i<6;i++){
        GPIOC->ODR ^= (1U<<9); // PC9
        for(volatile int i=0;i<80000;i++){}
    }
    
    /* Before Entering into Update logic, check Host is Ready*/
    UART_Send_Data(READY);
    UART_Send_Data(ACK);
    
    uint8_t uart_status = UART_Receive_Data();
    if(uart_status==ACK){
        uint32_t current_flash_write_address = APPLICATION_START_ADDR;
        while(1){

            uint8_t  Data_Buffer[MAX_PACKET_DATA_SIZE];
            uint8_t  received_cmd;
            uint16_t received_data_len;
            uint8_t  received_crc;
            uint8_t  received_end_byte;
            uint8_t  calculated_crc_val;
            uint8_t  flash_op_status = ACK; // Assume success Initially
 
            /* 1. Wait for the Start Byte */
            while(UART_Receive_Data()!= START_BYTE);

            /* 2. Receive Command */
            received_cmd = UART_Receive_Data();

            /* 3. Receive Data Length (1 byte) */
            received_data_len = UART_Receive_Data();

            if(received_data_len > MAX_PACKET_DATA_SIZE){
                /* Invalid Length, Send NACK & restart reception*/
                UART_Send_Data(NACK);
                continue;   //Exits while loop & wait for SB(Start Byte)
            }

            /* 4. Receive Data */
            for(uint16_t i=0;i<received_data_len;i++){
                Data_Buffer[i] = UART_Receive_Data();
            }

            /* 5. Receive CRC & END_BYTE */
            received_crc = UART_Receive_Data();
            received_end_byte = UART_Receive_Data();

            // 6. Calculate CRC on received data (from command byte to end of payload)
            // The CRC calculation must include all fields that the host sends,
            calculated_crc_val = received_cmd;
            calculated_crc_val += received_data_len;
            calculated_crc_val += Calculated_Checksum(Data_Buffer, received_data_len); // Your existing function

            /* 7. Validate CRC and END_BYTE */
            if (received_crc != calculated_crc_val || received_end_byte != END_BYTE) {
                UART_Send_Data(NACK); // Send NACK if validation fails
                continue; // Restart packet reception
            }

            UART_Send_Data(ACK);

            /* If CRC is Validated */
            switch(received_cmd){
                uint16_t halfword_data;

                case ERASE:
                    UART_Send_Data(ACK); // Send ACK for erase operation
                    flash_op_status = Flash_Memory_Erase_Pages(APPLICATION_START_ADDR, BOOT_FLASH_NUM_PAGES);
                    if(flash_op_status == FLASH_OK){
                        UART_Send_Data(ACK);
                        current_flash_write_address = APPLICATION_START_ADDR; // Reset address
                    } else {
                        UART_Send_Data(NACK); // Send NACK for erase failure
                    }
                    break;
                case WRITE:
                    // Iterate through Data_Buffer in 2-byte chunks.
                    for(uint16_t i = 0; i < received_data_len; i += 2){
                        if (i + 1 < received_data_len) { // Check if there's a second byte
                            halfword_data = (uint16_t)Data_Buffer[i] | ((uint16_t)Data_Buffer[i+1] << 8);
                        } else { // Odd number of bytes, pad last halfword with 0xFF
                            halfword_data = (uint16_t)Data_Buffer[i] | 0xFF00;
                        }
                        // Write to the current_flash_write_address, incrementing for each halfword
                        flash_op_status = Flash_Program_Halfword(current_flash_write_address, halfword_data);
                        if (flash_op_status != FLASH_OK) {
                            break; // Exit loop on first error
                        }
                        current_flash_write_address += sizeof(uint16_t); // Move to next halfword address
                    }
                    if(flash_op_status == FLASH_OK){
                        UART_Send_Data(ACK); // Send ACK for write operation
                    } else {
                        UART_Send_Data(NACK); // Send NACK for write failure
                    }
                    break;
                case JUMP:
                    // Before jumping, ensure all flash operations are complete and locked
                    Flash_Memory_Lock(); // Ensure flash is locked after all operations

                    if(application_valid()){
                        UART_Send_Data(ACK); // Let host know we're about to jump
                        __disable_irq(); // Disable interrupts before jumping

                    /* Disable SysTick counter, interrupt, and clock source*/
                    SysTick->CTRL = 0;
                    SysTick->LOAD = 0;
                    SysTick->VAL  = 0;

                    /* Reset UART2 Peripheral before Jump */
                    RCC->APB1RSTR |= RCC_APB1RSTR_USART2RST;
                    RCC->APB1RSTR &= ~RCC_APB1RSTR_USART2RST;
                    /* Reset GPIO's */
                    RCC->AHBRSTR |= RCC_AHBRSTR_GPIOARST; // Reset GPIOA
                    RCC->AHBRSTR &= ~RCC_AHBRSTR_GPIOARST;
                    RCC->AHBRSTR |= RCC_AHBRSTR_GPIOCRST; // Reset GPIOC
                    RCC->AHBRSTR &= ~RCC_AHBRSTR_GPIOCRST;

                    /* Clear all pending interrupt flags in NVIC */
                    for(uint8_t i = 0; i < 32; i++) {
                        NVIC->ICER[i >> 5] = (1UL << (i & 0x1F)); // Disable interrupt
                        NVIC->ICPR[i >> 5] = (1UL << (i & 0x1F)); // Clear pending flag
                    }
                    // Also clear any pending System Handler Control and State Register (SHCSR) faults if desired
                    SCB->SHCSR = 0;
                    __DSB();
                    __ISB();
                    
                    // Re-copy Application's Vector Table from Flash to RAM 
                    volatile uint32_t *app_flash_vec_table = (volatile uint32_t*)APPLICATION_START_ADDR;
                    volatile uint32_t *ram_vec_table_ptr_local = (volatile uint32_t*)RAM_VECTOR_TABLE_ADDR;
                    for (int i = 0; i < VECTOR_TABLE_SIZE_WORDS; i++) {
                        ram_vec_table_ptr_local[i] = app_flash_vec_table[i];
                    }
                    __DSB();
                    __ISB();

                    uint32_t app_msp = *(volatile uint32_t*)RAM_VECTOR_TABLE_ADDR;
                    uint32_t reset_handler_address = *(volatile uint32_t*)(RAM_VECTOR_TABLE_ADDR + 4);

                    __set_MSP(app_msp);

                    typedef void (*pFunction)(void);
                    pFunction jump_to_app = (pFunction)(reset_handler_address | 0x1);
                    jump_to_app();
                    // Should not return here
                    } else {
                        UART_Send_Data(NACK); // Inform host of validation failure
                    }
                    break;

                default:
                    UART_Send_Data(NACK); // Unknown command
                    break;
            }
        }
    }
    else{
        while(1){
            for(volatile int i=0;i<80000;i++){}
            GPIOC->ODR ^= (1U<<9);
        }
    }
}

uint8_t Calculated_Checksum(const uint8_t *Data, uint8_t Length){
    uint8_t Data_CRC = 0;
    for(uint16_t i=0;i<Length;i++){
        Data_CRC += Data[i];
    }
    return Data_CRC;
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
        (app_reset_handler >= (APPLICATION_START_ADDR + 44U * 1024U)) ||
        ((app_reset_handler & 0x1) == 0)) { // Check if LSB is 0 (should be 1 for Thumb)
        return false;
    }
    return true;
}