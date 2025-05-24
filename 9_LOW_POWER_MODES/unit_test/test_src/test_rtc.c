#include "main.h"

void test_rtc_initialization(void){
    RTC_Init();
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x53,RTC->WPR,"Not a correct Key"); /* Last key added */
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x007C013F,RTC->PRER,"Not a correct Prescalar value");
    RTC_Set_Time('A',7,0,0);
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x70000,RTC->TR,"Not a correct time set");
}