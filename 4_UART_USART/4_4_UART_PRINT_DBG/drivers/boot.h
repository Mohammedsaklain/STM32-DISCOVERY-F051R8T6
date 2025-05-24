#ifndef BOOT_H_
#define BOOT_H_
    #include "main.h"
    #define APPLICATION_START_ADDR  0x08004000UL
    #define RAM_BASE                0x20000000UL
    #define RAM_SIZE                0x00002000UL
    #define RAM_VECTOR_TABLE_ADDR   (RAM_BASE) // Define the RAM location for the vector table
    // size of the vector table (16 core + 32 external IRQs for STM32F0)
    #define VECTOR_TABLE_SIZE_WORDS (16 + 32) // 48 entries
    #define VECTOR_TABLE_SIZE_BYTES (VECTOR_TABLE_SIZE_WORDS * 4) // 192 bytes

#endif
