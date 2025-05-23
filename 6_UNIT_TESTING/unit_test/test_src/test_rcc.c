#include "main.h"
#include "unity.h"
#include "test_stm32f0xx.h"

void test_rcc_initialization(void){
    rcc_clock_config();
    TEST_ASSERT_EQUAL_HEX32(0x1,RCC->CR);                   /* Check whether HSI is ON*/
    TEST_ASSERT_EQUAL_HEX32(0,RCC->CFGR);                   /* Check HSI as System Clk, NO SYSCLK & HCLK divided*/
    TEST_ASSERT_EQUAL_HEX32((RCC_AHBENR_GPIOAEN|RCC_AHBENR_GPIOCEN), RCC->AHBENR); /* Check GPIOA & C, Clock enabled ?*/
}
