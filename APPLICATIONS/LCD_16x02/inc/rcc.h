#ifndef RCC_H_
#define RCC_H_

#include "stm32f0xx.h"

#define GPIO_CLK
#define I2C__1_2_APB1_CLK

#undef TIMER__2_3_6_14_APB1_CLK
#undef TIMER__1_15_16_17_APB2_CLK

void rcc_clock_config(void);
#endif