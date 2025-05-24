#include "main.h"
#include "unity.h"
#include "test_stm32f0xx.h"

void test_gpio_initialization(void){
    origin();  /* Call Origin*/
    TEST_ASSERT_EQUAL_HEX32(0x00050000,GPIOC->MODER); /* Test PC8 & PC9 active ?*/
}