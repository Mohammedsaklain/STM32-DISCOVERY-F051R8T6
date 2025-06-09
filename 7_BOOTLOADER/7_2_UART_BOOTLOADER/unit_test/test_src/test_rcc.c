#include "main.h"

void test_rcc_initialization(void){
    rcc_clock_config();
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x1,RCC->CR,"HSI is not ON");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(0,RCC->CFGR,"Either No HSI as System Clk, division of SYSCLK & HCLK happened");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE((RCC_AHBENR_GPIOAEN|RCC_AHBENR_GPIOCEN), RCC->AHBENR,"GPIOA & C, Clk not enabled");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(RCC_APB1ENR_PWREN,RCC->APB1ENR,"Power Clock not Enabled");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(PWR_CR_DBP,PWR->CR,"RTC domain write protection not disabled");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE((RCC_BDCR_RTCSEL_1 | RCC_BDCR_RTCEN),RCC->BDCR,"RTC clk not Enabled or NO selection of LSI-40 KHz clk for RTC");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(RCC_CSR_LSION,RCC->CSR,"LSI Clk not enabled");
}
