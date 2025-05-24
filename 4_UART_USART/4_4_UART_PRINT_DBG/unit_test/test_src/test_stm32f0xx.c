#include "main.h"
#include "test_stm32f0xx.h"

/* Initially making all the values to zero*/
RCC_TypeDef reg_sim_RCC = {0};
GPIO_TypeDef reg_sim_GPIO = {0};
RTC_TypeDef reg_sim_RTC = {0};
PWR_TypeDef reg_sim_PWR = {0};