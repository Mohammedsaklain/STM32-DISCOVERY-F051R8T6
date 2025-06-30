#ifndef RCC_H_
#define RCC_H_

#define SYSTEM_CLK 8000000UL

/* Active clocks*/
#define GPIO_CLK
#define USART__2_CLK

/* In-active clocks*/
#undef RTC_CLK
#undef ADC_CLK_EN
#undef I2C__1_2_APB1_CLK
#undef TIMER__2_3_6_14_APB1_CLK
#undef TIMER__1_15_16_17_APB2_CLK
#undef LOW_POWER_MODES
//#undef EXTERNAL_INTERRUPT

void rcc_clock_config(void);
#endif