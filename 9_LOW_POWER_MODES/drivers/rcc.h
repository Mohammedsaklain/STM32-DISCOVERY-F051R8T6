#ifndef RCC_H_
#define RCC_H_

#include "main.h"

/* Active clocks*/
#define GPIO_CLK
#define USART__2_CLK
#define EXTERNAL_INTERRUPT
#define LOW_POWER_MODES
/* In-active clocks*/
#undef RTC_CLK
#undef I2C__1_2_APB1_CLK
#undef TIMER__2_3_6_14_APB1_CLK
#undef TIMER__1_15_16_17_APB2_CLK

void rcc_clock_config(void);
#endif