#include "main.h"
#include "unity.h"
#include "test_stm32f0xx.h"

extern void test_rcc_initialization(void);
extern void test_rtc_initialization(void);

void setUp(void){
    /* Initially make all values to Zero or to default values*/
    reg_sim_RCC.AHBENR = 0; 
    reg_sim_RTC.TR = 0;
    reg_sim_RTC.PRER = 0x007F00FF;
    reg_sim_RTC.ISR = 0x00000007;
}

void tearDown(void){}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_rcc_initialization);
    RUN_TEST(test_rtc_initialization);
    return UNITY_END();
}
