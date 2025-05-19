#include "main.h"
#include "unity.h"
#include "test_stm32f0xx.h"

void setUp(void){
    reg_sim_RCC.AHBENR = 0;
}

void tearDown(void){}

void test_rcc_gpio_initialization(void){
    rcc_clock_config();
    TEST_ASSERT_BITS_HIGH(RCC_AHBENR_GPIOAEN, RCC->AHBENR);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_rcc_gpio_initialization);
    return UNITY_END();
}