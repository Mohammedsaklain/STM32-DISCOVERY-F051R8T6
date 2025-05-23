#include "main.h"
#include "unity.h"
#include "test_stm32f0xx.h"

extern void test_rcc_initialization(void);
extern void test_gpio_initialization(void);

void setUp(void){
    reg_sim_RCC.AHBENR = 0; //Initially make all values to Zero
    reg_sim_GPIO.MODER = 0;
}

void tearDown(void){}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_rcc_initialization);
    RUN_TEST(test_gpio_initialization);
    return UNITY_END();
}
