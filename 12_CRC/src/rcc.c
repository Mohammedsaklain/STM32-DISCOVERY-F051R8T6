/* file:    rcc.c */
#include "custom.h"
#include "rcc.h"

void rcc_clock_config(void)
{
    RCC->CR|= RCC_CR_HSION;                     // Enabling HSI
    #ifndef HOST_UNIT_TEST
        while(!(RCC->CR & RCC_CR_HSIRDY));      // Make sure that HSI is Ready
    #endif
    RCC->CFGR&= ~RCC_CFGR_SW;                   // HSI Selected as System CLK
    RCC->CFGR|= RCC_CFGR_HPRE_DIV1;             // AHB prescaler to 1 (ie NO SYSCLK divided)
    RCC->CFGR|= RCC_CFGR_PPRE_DIV1;             // NO HCLK divided
   
    #ifdef GPIO_CLK
        RCC->AHBENR  |= (RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN);     // Enable Clk for IO
    #endif

    #ifdef USART__2_CLK
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    #endif
    
    #ifdef TIMER__2_3_6_14_APB1_CLK             // Timer Clk
        RCC->APB1ENR |= (RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN);
    #endif

    #ifdef TIMER__1_15_16_17_APB2_CLK
        RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;
    #endif

    #ifdef ADC_CLK_EN
        ADC1->CFGR2 &= ~ADC_CFGR2_CKMODE;               // Asynchronous clock(ie internal HSI14 clock)
        RCC->CR2 |= RCC_CR2_HSI14ON;                    // Enable HSI14 Clock(14MHz)
        while(!((RCC->CR2) & (RCC_CR2_HSI14RDY)));      // wait for HSI14 Clk to be ready
        RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;             // Enable ADC1 Clock
    #endif

    #ifdef I2C__1_2_APB1_CLK
        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    #endif

    #ifdef EXTERNAL_INTERRUPT
        RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;   // Enable SYSCFG clock, used for ext int.
    #endif

    #ifdef LOW_POWER_MODES
        RCC->APB1ENR |= RCC_APB1ENR_PWREN;      // Power Interface clock enable
    #endif

    #ifdef RTC_CLK
        RCC->APB1ENR |= RCC_APB1ENR_PWREN;      // Power Clock Enable
        PWR->CR   |= PWR_CR_DBP;                // Disable RTC domain Write protection
        RCC->BDCR |= RCC_BDCR_RTCSEL_1;         // Select LSI-40 KHz clk for RTC
        RCC->CSR  |= RCC_CSR_LSION;             // Enable LSI Clk
        #ifndef HOST_UNIT_TEST    
            while(!((RCC->CSR) & (RCC_CSR_LSIRDY))){} // Make sure LSI Clk ready 
        #endif
        RCC->BDCR |= RCC_BDCR_RTCEN;            // Enable RTC clk
    #endif

    #ifdef BOOTLOADER
        RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;       // SYSCFG clk enable(for vector table offsetting)
    #endif
}
