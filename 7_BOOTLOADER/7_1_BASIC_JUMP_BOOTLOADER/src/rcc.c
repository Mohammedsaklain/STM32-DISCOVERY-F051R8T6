/* file:    rcc.c */
#include "main.h"

void rcc_clock_config(void)
{
    RCC->CR|= RCC_CR_HSION;                     // Enabling HSI
    while(!(RCC->CR & RCC_CR_HSIRDY));          // Make sure that HSI is Ready
    RCC->CFGR&= ~RCC_CFGR_SW;                   // HSI Selected as System CLK
    RCC->CFGR|= RCC_CFGR_HPRE_DIV1;             // AHB prescaler to 1 (ie NO SYSCLK divided)
    RCC->CFGR|= RCC_CFGR_PPRE_DIV1;             // NO HCLK divided

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;       // SYSCFG clk enable(for vector table offsetting)
    RCC->APB2ENR |= 1<<0;                       // Enable clock for System Clock Configuration(INT)
    #ifdef GPIO_CLK
        RCC->AHBENR  |= (RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN);     // Enable Clk for IO
    #endif

    #ifdef I2C__1_2_APB1_CLK
        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    #endif

    #ifdef TIMER__2_3_6_14_APB1_CLK             // Timer Clk
        RCC->APB1ENR |= (RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN);
    #endif

    #ifdef TIMER__1_15_16_17_APB2_CLK
        RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;
    #endif
}