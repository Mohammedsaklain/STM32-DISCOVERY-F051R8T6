#ifndef TEST_STM32F0XX_H_
#define TEST_STM32F0XX_H_

#include "stdint.h"


/******************************************************************************/
/*                                                                            */
/*                         Reset and Clock Control                            */
/*                                                                            */
/******************************************************************************/


typedef struct
{
  volatile uint32_t CR;         /*!< RCC clock control register */
  volatile uint32_t CFGR;       /*!< RCC clock configuration register*/
  volatile uint32_t CIR;        /*!< RCC clock interrupt register*/
  volatile uint32_t APB2RSTR;   /*!< RCC APB2 peripheral reset register*/
  volatile uint32_t APB1RSTR;   /*!< RCC APB1 peripheral reset register*/
  volatile uint32_t AHBENR;     /*!< RCC AHB peripheral clock register*/
  volatile uint32_t APB2ENR;    /*!< RCC APB2 peripheral clock enable register*/
  volatile uint32_t APB1ENR;    /*!< RCC APB1 peripheral clock enable register*/
  volatile uint32_t BDCR;       /*!< RCC Backup domain control register*/ 
  volatile uint32_t CSR;        /*!< RCC clock control & status register*/
  volatile uint32_t AHBRSTR;    /*!< RCC AHB peripheral reset register*/
  volatile uint32_t CFGR2;      /*!< RCC clock configuration register 2*/
  volatile uint32_t CFGR3;      /*!< RCC clock configuration register 3*/
  volatile uint32_t CR2;        /*!< RCC clock control register 2*/
} RCC_TypeDef;


extern RCC_TypeDef reg_sim_RCC;
#define RCC (&reg_sim_RCC)

/********************  Bit definition for RCC_CR register  ********************/
#define  RCC_CR_HSION                        ((uint32_t)0x00000001)        /*!< Internal High Speed clock enable */
#define  RCC_CR_HSIRDY                       ((uint32_t)0x00000002)        /*!< Internal High Speed clock ready flag */
#define  RCC_CR_HSITRIM                      ((uint32_t)0x000000F8)        /*!< Internal High Speed clock trimming */
#define  RCC_CR_HSICAL                       ((uint32_t)0x0000FF00)        /*!< Internal High Speed clock Calibration */
#define  RCC_CR_HSEON                        ((uint32_t)0x00010000)        /*!< External High Speed clock enable */
#define  RCC_CR_HSERDY                       ((uint32_t)0x00020000)        /*!< External High Speed clock ready flag */
#define  RCC_CR_HSEBYP                       ((uint32_t)0x00040000)        /*!< External High Speed clock Bypass */
#define  RCC_CR_CSSON                        ((uint32_t)0x00080000)        /*!< Clock Security System enable */
#define  RCC_CR_PLLON                        ((uint32_t)0x01000000)        /*!< PLL enable */
#define  RCC_CR_PLLRDY                       ((uint32_t)0x02000000)        /*!< PLL clock ready flag */

/*******************  Bit definition for RCC_CFGR register  *******************/
#define  RCC_CFGR_SW                         ((uint32_t)0x00000003)        /*!< SW[1:0] bits (System clock Switch) */
#define  RCC_CFGR_SW_0                       ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  RCC_CFGR_SW_1                       ((uint32_t)0x00000002)        /*!< Bit 1 */
/* SW configuration */
#define  RCC_CFGR_SW_HSI                     ((uint32_t)0x00000000)        /*!< HSI selected as system clock */
#define  RCC_CFGR_SW_HSE                     ((uint32_t)0x00000001)        /*!< HSE selected as system clock */
#define  RCC_CFGR_SW_PLL                     ((uint32_t)0x00000002)        /*!< PLL selected as system clock */
#define  RCC_CFGR_SW_HSI48                   ((uint32_t)0x00000003)        /*!< HSI48 selected as system clock */

#define  RCC_CFGR_SWS                        ((uint32_t)0x0000000C)        /*!< SWS[1:0] bits (System Clock Switch Status) */
#define  RCC_CFGR_SWS_0                      ((uint32_t)0x00000004)        /*!< Bit 0 */
#define  RCC_CFGR_SWS_1                      ((uint32_t)0x00000008)        /*!< Bit 1 */
/* SWS configuration */
#define  RCC_CFGR_SWS_HSI                    ((uint32_t)0x00000000)        /*!< HSI oscillator used as system clock */
#define  RCC_CFGR_SWS_HSE                    ((uint32_t)0x00000004)        /*!< HSE oscillator used as system clock */
#define  RCC_CFGR_SWS_PLL                    ((uint32_t)0x00000008)        /*!< PLL used as system clock */
#define  RCC_CFGR_SWS_HSI48                  ((uint32_t)0x0000000C)        /*!< HSI48 used as system clock */

#define  RCC_CFGR_HPRE                       ((uint32_t)0x000000F0)        /*!< HPRE[3:0] bits (AHB prescaler) */
#define  RCC_CFGR_HPRE_0                     ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  RCC_CFGR_HPRE_1                     ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  RCC_CFGR_HPRE_2                     ((uint32_t)0x00000040)        /*!< Bit 2 */
#define  RCC_CFGR_HPRE_3                     ((uint32_t)0x00000080)        /*!< Bit 3 */
/* HPRE configuration */
#define  RCC_CFGR_HPRE_DIV1                  ((uint32_t)0x00000000)        /*!< SYSCLK not divided */
#define  RCC_CFGR_HPRE_DIV2                  ((uint32_t)0x00000080)        /*!< SYSCLK divided by 2 */
#define  RCC_CFGR_HPRE_DIV4                  ((uint32_t)0x00000090)        /*!< SYSCLK divided by 4 */
#define  RCC_CFGR_HPRE_DIV8                  ((uint32_t)0x000000A0)        /*!< SYSCLK divided by 8 */
#define  RCC_CFGR_HPRE_DIV16                 ((uint32_t)0x000000B0)        /*!< SYSCLK divided by 16 */
#define  RCC_CFGR_HPRE_DIV64                 ((uint32_t)0x000000C0)        /*!< SYSCLK divided by 64 */
#define  RCC_CFGR_HPRE_DIV128                ((uint32_t)0x000000D0)        /*!< SYSCLK divided by 128 */
#define  RCC_CFGR_HPRE_DIV256                ((uint32_t)0x000000E0)        /*!< SYSCLK divided by 256 */
#define  RCC_CFGR_HPRE_DIV512                ((uint32_t)0x000000F0)        /*!< SYSCLK divided by 512 */

#define  RCC_CFGR_PPRE                       ((uint32_t)0x00000700)        /*!< PRE[2:0] bits (APB prescaler) */
#define  RCC_CFGR_PPRE_0                     ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  RCC_CFGR_PPRE_1                     ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  RCC_CFGR_PPRE_2                     ((uint32_t)0x00000400)        /*!< Bit 2 */
/* PPRE configuration */
#define  RCC_CFGR_PPRE_DIV1                  ((uint32_t)0x00000000)        /*!< HCLK not divided */
#define  RCC_CFGR_PPRE_DIV2                  ((uint32_t)0x00000400)        /*!< HCLK divided by 2 */
#define  RCC_CFGR_PPRE_DIV4                  ((uint32_t)0x00000500)        /*!< HCLK divided by 4 */
#define  RCC_CFGR_PPRE_DIV8                  ((uint32_t)0x00000600)        /*!< HCLK divided by 8 */
#define  RCC_CFGR_PPRE_DIV16                 ((uint32_t)0x00000700)        /*!< HCLK divided by 16 */

#define  RCC_CFGR_ADCPRE                     ((uint32_t)0x00004000)        /*!< ADC prescaler: Obsolete. Proper ADC clock selection is 
                                                                                done inside the ADC_CFGR2 */

#define  RCC_CFGR_PLLSRC                     ((uint32_t)0x00018000)        /*!< PLL entry clock source */
#define  RCC_CFGR_PLLSRC_0                   ((uint32_t)0x00008000)        /*!< Bit 0 (available only in the STM32F072 devices) */
#define  RCC_CFGR_PLLSRC_1                   ((uint32_t)0x00010000)        /*!< Bit 1 */

#define  RCC_CFGR_PLLSRC_PREDIV1             ((uint32_t)0x00010000)        /*!< PREDIV1 clock selected as PLL entry clock source; 
                                                                                Old PREDIV1 bit definition, maintained for legacy purpose */
#define  RCC_CFGR_PLLSRC_HSI_DIV2            ((uint32_t)0x00000000)        /*!< HSI clock divided by 2 selected as PLL entry clock source */
#define  RCC_CFGR_PLLSRC_HSI_PREDIV          ((uint32_t)0x00008000)        /*!< HSI PREDIV clock selected as PLL entry clock source 
                                                                                (This bit and configuration is only available for STM32F072 devices)*/
#define  RCC_CFGR_PLLSRC_HSE_PREDIV          ((uint32_t)0x00010000)        /*!< HSE PREDIV clock selected as PLL entry clock source */
#define  RCC_CFGR_PLLSRC_HSI48_PREDIV        ((uint32_t)0x00018000)        /*!< HSI48 PREDIV clock selected as PLL entry clock source */

#define  RCC_CFGR_PLLXTPRE                   ((uint32_t)0x00020000)        /*!< HSE divider for PLL entry */
#define  RCC_CFGR_PLLXTPRE_PREDIV1           ((uint32_t)0x00000000)        /*!< PREDIV1 clock not divided for PLL entry */
#define  RCC_CFGR_PLLXTPRE_PREDIV1_Div2      ((uint32_t)0x00020000)        /*!< PREDIV1 clock divided by 2 for PLL entry */

/*!< Old bit definition maintained for legacy purposes */
#define  RCC_CFGR_PLLSRC_HSI_Div2            RCC_CFGR_PLLSRC_HSI_DIV2

/* PLLMUL configuration */
#define  RCC_CFGR_PLLMUL                    ((uint32_t)0x003C0000)        /*!< PLLMUL[3:0] bits (PLL multiplication factor) */
#define  RCC_CFGR_PLLMUL_0                  ((uint32_t)0x00040000)        /*!< Bit 0 */
#define  RCC_CFGR_PLLMUL_1                  ((uint32_t)0x00080000)        /*!< Bit 1 */
#define  RCC_CFGR_PLLMUL_2                  ((uint32_t)0x00100000)        /*!< Bit 2 */
#define  RCC_CFGR_PLLMUL_3                  ((uint32_t)0x00200000)        /*!< Bit 3 */

#define  RCC_CFGR_PLLMUL2                   ((uint32_t)0x00000000)        /*!< PLL input clock*2 */
#define  RCC_CFGR_PLLMUL3                   ((uint32_t)0x00040000)        /*!< PLL input clock*3 */
#define  RCC_CFGR_PLLMUL4                   ((uint32_t)0x00080000)        /*!< PLL input clock*4 */
#define  RCC_CFGR_PLLMUL5                   ((uint32_t)0x000C0000)        /*!< PLL input clock*5 */
#define  RCC_CFGR_PLLMUL6                   ((uint32_t)0x00100000)        /*!< PLL input clock*6 */
#define  RCC_CFGR_PLLMUL7                   ((uint32_t)0x00140000)        /*!< PLL input clock*7 */
#define  RCC_CFGR_PLLMUL8                   ((uint32_t)0x00180000)        /*!< PLL input clock*8 */
#define  RCC_CFGR_PLLMUL9                   ((uint32_t)0x001C0000)        /*!< PLL input clock*9 */
#define  RCC_CFGR_PLLMUL10                  ((uint32_t)0x00200000)        /*!< PLL input clock10 */
#define  RCC_CFGR_PLLMUL11                  ((uint32_t)0x00240000)        /*!< PLL input clock*11 */
#define  RCC_CFGR_PLLMUL12                  ((uint32_t)0x00280000)        /*!< PLL input clock*12 */
#define  RCC_CFGR_PLLMUL13                  ((uint32_t)0x002C0000)        /*!< PLL input clock*13 */
#define  RCC_CFGR_PLLMUL14                  ((uint32_t)0x00300000)        /*!< PLL input clock*14 */
#define  RCC_CFGR_PLLMUL15                  ((uint32_t)0x00340000)        /*!< PLL input clock*15 */
#define  RCC_CFGR_PLLMUL16                  ((uint32_t)0x00380000)        /*!< PLL input clock*16 */

/* Old PLLMUL configuration bit definition maintained for legacy purposes */
#define  RCC_CFGR_PLLMULL                    RCC_CFGR_PLLMUL        /*!< PLLMUL[3:0] bits (PLL multiplication factor) */
#define  RCC_CFGR_PLLMULL_0                  RCC_CFGR_PLLMUL_0        /*!< Bit 0 */
#define  RCC_CFGR_PLLMULL_1                  RCC_CFGR_PLLMUL_1        /*!< Bit 1 */
#define  RCC_CFGR_PLLMULL_2                  RCC_CFGR_PLLMUL_2        /*!< Bit 2 */
#define  RCC_CFGR_PLLMULL_3                  RCC_CFGR_PLLMUL_3       /*!< Bit 3 */

#define  RCC_CFGR_PLLMULL2                   RCC_CFGR_PLLMUL2       /*!< PLL input clock*2 */
#define  RCC_CFGR_PLLMULL3                   RCC_CFGR_PLLMUL3        /*!< PLL input clock*3 */
#define  RCC_CFGR_PLLMULL4                   RCC_CFGR_PLLMUL4        /*!< PLL input clock*4 */
#define  RCC_CFGR_PLLMULL5                   RCC_CFGR_PLLMUL5        /*!< PLL input clock*5 */
#define  RCC_CFGR_PLLMULL6                   RCC_CFGR_PLLMUL6        /*!< PLL input clock*6 */
#define  RCC_CFGR_PLLMULL7                   RCC_CFGR_PLLMUL7        /*!< PLL input clock*7 */
#define  RCC_CFGR_PLLMULL8                   RCC_CFGR_PLLMUL8        /*!< PLL input clock*8 */
#define  RCC_CFGR_PLLMULL9                   RCC_CFGR_PLLMUL9        /*!< PLL input clock*9 */
#define  RCC_CFGR_PLLMULL10                  RCC_CFGR_PLLMUL10        /*!< PLL input clock10 */
#define  RCC_CFGR_PLLMULL11                  RCC_CFGR_PLLMUL11        /*!< PLL input clock*11 */
#define  RCC_CFGR_PLLMULL12                  RCC_CFGR_PLLMUL12        /*!< PLL input clock*12 */
#define  RCC_CFGR_PLLMULL13                  RCC_CFGR_PLLMUL13        /*!< PLL input clock*13 */
#define  RCC_CFGR_PLLMULL14                  RCC_CFGR_PLLMUL14        /*!< PLL input clock*14 */
#define  RCC_CFGR_PLLMULL15                  RCC_CFGR_PLLMUL15        /*!< PLL input clock*15 */
#define  RCC_CFGR_PLLMULL16                  RCC_CFGR_PLLMUL16        /*!< PLL input clock*16 */

#define  RCC_CFGR_MCO                        ((uint32_t)0x0F000000)        /*!< MCO[2:0] bits (Microcontroller Clock Output) */
#define  RCC_CFGR_MCO_0                      ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  RCC_CFGR_MCO_1                      ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  RCC_CFGR_MCO_2                      ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  RCC_CFGR_MCO_3                      ((uint32_t)0x08000000)        /*!< Bit 3 */
/* MCO configuration */
#define  RCC_CFGR_MCO_NOCLOCK                ((uint32_t)0x00000000)        /*!< No clock */
#define  RCC_CFGR_MCO_HSI14                  ((uint32_t)0x01000000)        /*!< HSI14 clock selected as MCO source */
#define  RCC_CFGR_MCO_LSI                    ((uint32_t)0x02000000)        /*!< LSI clock selected as MCO source */
#define  RCC_CFGR_MCO_LSE                    ((uint32_t)0x03000000)        /*!< LSE clock selected as MCO source */
#define  RCC_CFGR_MCO_SYSCLK                 ((uint32_t)0x04000000)        /*!< System clock selected as MCO source */
#define  RCC_CFGR_MCO_HSI                    ((uint32_t)0x05000000)        /*!< HSI clock selected as MCO source */
#define  RCC_CFGR_MCO_HSE                    ((uint32_t)0x06000000)        /*!< HSE clock selected as MCO source  */
#define  RCC_CFGR_MCO_PLL                    ((uint32_t)0x07000000)        /*!< PLL clock selected as MCO source */
#define  RCC_CFGR_MCO_HSI48                  ((uint32_t)0x08000000)        /*!< HSI48 clock selected as MCO source */

#define  RCC_CFGR_MCO_PRE                    ((uint32_t)0x70000000)        /*!< MCO prescaler (these bits are not available in the STM32F051 devices)*/
#define  RCC_CFGR_MCO_PRE_1                  ((uint32_t)0x00000000)        /*!< MCO is divided by 1 (this bit are not available in the STM32F051 devices)*/
#define  RCC_CFGR_MCO_PRE_2                  ((uint32_t)0x10000000)        /*!< MCO is divided by 2 (this bit are not available in the STM32F051 devices)*/
#define  RCC_CFGR_MCO_PRE_4                  ((uint32_t)0x20000000)        /*!< MCO is divided by 4 (this bit are not available in the STM32F051 devices)*/
#define  RCC_CFGR_MCO_PRE_8                  ((uint32_t)0x30000000)        /*!< MCO is divided by 8 (this bit are not available in the STM32F051 devices)*/
#define  RCC_CFGR_MCO_PRE_16                 ((uint32_t)0x40000000)        /*!< MCO is divided by 16 (this bit are not available in the STM32F051 devices)*/
#define  RCC_CFGR_MCO_PRE_32                 ((uint32_t)0x50000000)        /*!< MCO is divided by 32 (this bit are not available in the STM32F051 devices)*/
#define  RCC_CFGR_MCO_PRE_64                 ((uint32_t)0x60000000)        /*!< MCO is divided by 64 (this bit are not available in the STM32F051 devices)*/
#define  RCC_CFGR_MCO_PRE_128                ((uint32_t)0x70000000)        /*!< MCO is divided by 128 (this bit are not available in the STM32F051 devices)*/

#define  RCC_CFGR_PLLNODIV                   ((uint32_t)0x80000000)        /*!< PLL is not divided to MCO (this bit are not available in the STM32F051 devices) */

/*******************  Bit definition for RCC_CIR register  ********************/
#define  RCC_CIR_LSIRDYF                     ((uint32_t)0x00000001)        /*!< LSI Ready Interrupt flag */
#define  RCC_CIR_LSERDYF                     ((uint32_t)0x00000002)        /*!< LSE Ready Interrupt flag */
#define  RCC_CIR_HSIRDYF                     ((uint32_t)0x00000004)        /*!< HSI Ready Interrupt flag */
#define  RCC_CIR_HSERDYF                     ((uint32_t)0x00000008)        /*!< HSE Ready Interrupt flag */
#define  RCC_CIR_PLLRDYF                     ((uint32_t)0x00000010)        /*!< PLL Ready Interrupt flag */
#define  RCC_CIR_HSI14RDYF                   ((uint32_t)0x00000020)        /*!< HSI14 Ready Interrupt flag */
#define  RCC_CIR_HSI48RDYF                   ((uint32_t)0x00000040)        /*!< HSI48 Ready Interrupt flag */
#define  RCC_CIR_CSSF                        ((uint32_t)0x00000080)        /*!< Clock Security System Interrupt flag */
#define  RCC_CIR_LSIRDYIE                    ((uint32_t)0x00000100)        /*!< LSI Ready Interrupt Enable */
#define  RCC_CIR_LSERDYIE                    ((uint32_t)0x00000200)        /*!< LSE Ready Interrupt Enable */
#define  RCC_CIR_HSIRDYIE                    ((uint32_t)0x00000400)        /*!< HSI Ready Interrupt Enable */
#define  RCC_CIR_HSERDYIE                    ((uint32_t)0x00000800)        /*!< HSE Ready Interrupt Enable */
#define  RCC_CIR_PLLRDYIE                    ((uint32_t)0x00001000)        /*!< PLL Ready Interrupt Enable */
#define  RCC_CIR_HSI14RDYIE                  ((uint32_t)0x00002000)        /*!< HSI14 Ready Interrupt Enable */
#define  RCC_CIR_HSI48RDYIE                  ((uint32_t)0x00004000)        /*!< HSI48 Ready Interrupt Enable */
#define  RCC_CIR_LSIRDYC                     ((uint32_t)0x00010000)        /*!< LSI Ready Interrupt Clear */
#define  RCC_CIR_LSERDYC                     ((uint32_t)0x00020000)        /*!< LSE Ready Interrupt Clear */
#define  RCC_CIR_HSIRDYC                     ((uint32_t)0x00040000)        /*!< HSI Ready Interrupt Clear */
#define  RCC_CIR_HSERDYC                     ((uint32_t)0x00080000)        /*!< HSE Ready Interrupt Clear */
#define  RCC_CIR_PLLRDYC                     ((uint32_t)0x00100000)        /*!< PLL Ready Interrupt Clear */
#define  RCC_CIR_HSI14RDYC                   ((uint32_t)0x00200000)        /*!< HSI14 Ready Interrupt Clear */
#define  RCC_CIR_HSI48RDYC                   ((uint32_t)0x00400000)        /*!< HSI48 Ready Interrupt Clear */
#define  RCC_CIR_CSSC                        ((uint32_t)0x00800000)        /*!< Clock Security System Interrupt Clear */

/*****************  Bit definition for RCC_APB2RSTR register  *****************/
#define  RCC_APB2RSTR_SYSCFGRST              ((uint32_t)0x00000001)        /*!< SYSCFG clock reset */
#define  RCC_APB2RSTR_ADCRST                 ((uint32_t)0x00000200)        /*!< ADC clock reset */
#define  RCC_APB2RSTR_USART8RST              ((uint32_t)0x00000080)        /*!< USART8 clock reset */
#define  RCC_APB2RSTR_USART7RST              ((uint32_t)0x00000040)        /*!< USART7 clock reset */
#define  RCC_APB2RSTR_USART6RST              ((uint32_t)0x00000020)        /*!< USART6 clock reset */
#define  RCC_APB2RSTR_TIM1RST                ((uint32_t)0x00000800)        /*!< TIM1 clock reset */
#define  RCC_APB2RSTR_SPI1RST                ((uint32_t)0x00001000)        /*!< SPI1 clock reset */
#define  RCC_APB2RSTR_USART1RST              ((uint32_t)0x00004000)        /*!< USART1 clock reset */
#define  RCC_APB2RSTR_TIM15RST               ((uint32_t)0x00010000)        /*!< TIM15 clock reset */
#define  RCC_APB2RSTR_TIM16RST               ((uint32_t)0x00020000)        /*!< TIM16 clock reset */
#define  RCC_APB2RSTR_TIM17RST               ((uint32_t)0x00040000)        /*!< TIM17 clock reset */
#define  RCC_APB2RSTR_DBGMCURST              ((uint32_t)0x00400000)        /*!< DBGMCU clock reset */

/* Old ADC1 clock reset bit definition maintained for legacy purpose */
#define  RCC_APB2RSTR_ADC1RST                RCC_APB2RSTR_ADCRST          

/*****************  Bit definition for RCC_APB1RSTR register  *****************/
#define  RCC_APB1RSTR_TIM2RST                ((uint32_t)0x00000001)        /*!< Timer 2 clock reset */
#define  RCC_APB1RSTR_TIM3RST                ((uint32_t)0x00000002)        /*!< Timer 3 clock reset */
#define  RCC_APB1RSTR_TIM6RST                ((uint32_t)0x00000010)        /*!< Timer 6 clock reset */
#define  RCC_APB1RSTR_TIM7RST                ((uint32_t)0x00000020)        /*!< Timer 7 clock reset */
#define  RCC_APB1RSTR_TIM14RST               ((uint32_t)0x00000100)        /*!< Timer 14 clock reset */
#define  RCC_APB1RSTR_WWDGRST                ((uint32_t)0x00000800)        /*!< Window Watchdog clock reset */
#define  RCC_APB1RSTR_SPI2RST                ((uint32_t)0x00004000)        /*!< SPI2 clock reset */
#define  RCC_APB1RSTR_USART2RST              ((uint32_t)0x00020000)        /*!< USART 2 clock reset */
#define  RCC_APB1RSTR_USART3RST              ((uint32_t)0x00040000)        /*!< USART 3 clock reset */
#define  RCC_APB1RSTR_USART4RST              ((uint32_t)0x00080000)        /*!< USART 4 clock reset */
#define  RCC_APB1RSTR_USART5RST              ((uint32_t)0x00100000)        /*!< USART 5 clock reset */
#define  RCC_APB1RSTR_I2C1RST                ((uint32_t)0x00200000)        /*!< I2C 1 clock reset */
#define  RCC_APB1RSTR_I2C2RST                ((uint32_t)0x00400000)        /*!< I2C 2 clock reset */
#define  RCC_APB1RSTR_USBRST                 ((uint32_t)0x00800000)        /*!< USB clock reset */
#define  RCC_APB1RSTR_CANRST                 ((uint32_t)0x02000000)        /*!< CAN clock reset */
#define  RCC_APB1RSTR_CRSRST                 ((uint32_t)0x08000000)        /*!< CRS clock reset */
#define  RCC_APB1RSTR_PWRRST                 ((uint32_t)0x10000000)        /*!< PWR clock reset */
#define  RCC_APB1RSTR_DACRST                 ((uint32_t)0x20000000)        /*!< DAC clock reset */
#define  RCC_APB1RSTR_CECRST                 ((uint32_t)0x40000000)        /*!< CEC clock reset */

/******************  Bit definition for RCC_AHBENR register  ******************/
#define  RCC_AHBENR_DMAEN                    ((uint32_t)0x00000001)        /*!< DMA clock enable */
#define  RCC_AHBENR_DMA2EN                   ((uint32_t)0x00000002)        /*!< DMA2 clock enable */
#define  RCC_AHBENR_SRAMEN                   ((uint32_t)0x00000004)        /*!< SRAM interface clock enable */
#define  RCC_AHBENR_FLITFEN                  ((uint32_t)0x00000010)        /*!< FLITF clock enable */
#define  RCC_AHBENR_CRCEN                    ((uint32_t)0x00000040)        /*!< CRC clock enable */
#define  RCC_AHBENR_GPIOAEN                  ((uint32_t)0x00020000)        /*!< GPIOA clock enable */
#define  RCC_AHBENR_GPIOBEN                  ((uint32_t)0x00040000)        /*!< GPIOB clock enable */
#define  RCC_AHBENR_GPIOCEN                  ((uint32_t)0x00080000)        /*!< GPIOC clock enable */
#define  RCC_AHBENR_GPIODEN                  ((uint32_t)0x00100000)        /*!< GPIOD clock enable */
#define  RCC_AHBENR_GPIOEEN                  ((uint32_t)0x00200000)        /*!< GPIOE clock enable */
#define  RCC_AHBENR_GPIOFEN                  ((uint32_t)0x00400000)        /*!< GPIOF clock enable */
#define  RCC_AHBENR_TSCEN                    ((uint32_t)0x01000000)        /*!< TS controller clock enable */

/* Old Bit definition maintained for legacy purpose */
#define  RCC_AHBENR_DMA1EN                   RCC_AHBENR_DMAEN        /*!< DMA1 clock enable */
#define  RCC_AHBENR_TSEN                     RCC_AHBENR_TSCEN        /*!< TS clock enable */

/*****************  Bit definition for RCC_APB2ENR register  ******************/
#define  RCC_APB2ENR_SYSCFGCOMPEN            ((uint32_t)0x00000001)        /*!< SYSCFG and comparator clock enable */
#define  RCC_APB2ENR_USART6EN                ((uint32_t)0x00000020)        /*!< USART6 clock enable */
#define  RCC_APB2ENR_USART7EN                ((uint32_t)0x00000040)        /*!< USART7 clock enable */
#define  RCC_APB2ENR_USART8EN                ((uint32_t)0x00000080)        /*!< USART8 clock enable */
#define  RCC_APB2ENR_ADCEN                   ((uint32_t)0x00000200)        /*!< ADC1 clock enable */
#define  RCC_APB2ENR_TIM1EN                  ((uint32_t)0x00000800)        /*!< TIM1 clock enable */
#define  RCC_APB2ENR_SPI1EN                  ((uint32_t)0x00001000)        /*!< SPI1 clock enable */
#define  RCC_APB2ENR_USART1EN                ((uint32_t)0x00004000)        /*!< USART1 clock enable */
#define  RCC_APB2ENR_TIM15EN                 ((uint32_t)0x00010000)        /*!< TIM15 clock enable */
#define  RCC_APB2ENR_TIM16EN                 ((uint32_t)0x00020000)        /*!< TIM16 clock enable */
#define  RCC_APB2ENR_TIM17EN                 ((uint32_t)0x00040000)        /*!< TIM17 clock enable */
#define  RCC_APB2ENR_DBGMCUEN                ((uint32_t)0x00400000)        /*!< DBGMCU clock enable */

/* Old Bit definition maintained for legacy purpose */
#define  RCC_APB2ENR_SYSCFGEN                RCC_APB2ENR_SYSCFGCOMPEN        /*!< SYSCFG clock enable */
#define  RCC_APB2ENR_ADC1EN                  RCC_APB2ENR_ADCEN               /*!< ADC1 clock enable */

/*****************  Bit definition for RCC_APB1ENR register  ******************/
#define  RCC_APB1ENR_TIM2EN                  ((uint32_t)0x00000001)        /*!< Timer 2 clock enable */
#define  RCC_APB1ENR_TIM3EN                  ((uint32_t)0x00000002)        /*!< Timer 3 clock enable */
#define  RCC_APB1ENR_TIM6EN                  ((uint32_t)0x00000010)        /*!< Timer 6 clock enable */
#define  RCC_APB1ENR_TIM7EN                  ((uint32_t)0x00000020)        /*!< Timer 7 clock enable */
#define  RCC_APB1ENR_TIM14EN                 ((uint32_t)0x00000100)        /*!< Timer 14 clock enable */
#define  RCC_APB1ENR_WWDGEN                  ((uint32_t)0x00000800)        /*!< Window Watchdog clock enable */
#define  RCC_APB1ENR_SPI2EN                  ((uint32_t)0x00004000)        /*!< SPI2 clock enable */
#define  RCC_APB1ENR_USART2EN                ((uint32_t)0x00020000)        /*!< USART2 clock enable */
#define  RCC_APB1ENR_USART3EN                ((uint32_t)0x00040000)        /*!< USART3 clock enable */
#define  RCC_APB1ENR_USART4EN                ((uint32_t)0x00080000)        /*!< USART4 clock enable */
#define  RCC_APB1ENR_USART5EN                ((uint32_t)0x00100000)        /*!< USART5 clock enable */
#define  RCC_APB1ENR_I2C1EN                  ((uint32_t)0x00200000)        /*!< I2C1 clock enable */
#define  RCC_APB1ENR_I2C2EN                  ((uint32_t)0x00400000)        /*!< I2C2 clock enable */
#define  RCC_APB1ENR_USBEN                   ((uint32_t)0x00800000)        /*!< USB clock enable */
#define  RCC_APB1ENR_CANEN                   ((uint32_t)0x02000000)         /*!< CAN clock enable */
#define  RCC_APB1ENR_CRSEN                   ((uint32_t)0x08000000)        /*!< CRS clock enable */
#define  RCC_APB1ENR_PWREN                   ((uint32_t)0x10000000)        /*!< PWR clock enable */
#define  RCC_APB1ENR_DACEN                   ((uint32_t)0x20000000)        /*!< DAC clock enable */
#define  RCC_APB1ENR_CECEN                   ((uint32_t)0x40000000)        /*!< CEC clock enable */

/*******************  Bit definition for RCC_BDCR register  *******************/
#define  RCC_BDCR_LSEON                      ((uint32_t)0x00000001)        /*!< External Low Speed oscillator enable */
#define  RCC_BDCR_LSERDY                     ((uint32_t)0x00000002)        /*!< External Low Speed oscillator Ready */
#define  RCC_BDCR_LSEBYP                     ((uint32_t)0x00000004)        /*!< External Low Speed oscillator Bypass */

#define  RCC_BDCR_LSEDRV                     ((uint32_t)0x00000018)        /*!< LSEDRV[1:0] bits (LSE Osc. drive capability) */
#define  RCC_BDCR_LSEDRV_0                   ((uint32_t)0x00000008)        /*!< Bit 0 */
#define  RCC_BDCR_LSEDRV_1                   ((uint32_t)0x00000010)        /*!< Bit 1 */

#define  RCC_BDCR_RTCSEL                     ((uint32_t)0x00000300)        /*!< RTCSEL[1:0] bits (RTC clock source selection) */
#define  RCC_BDCR_RTCSEL_0                   ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  RCC_BDCR_RTCSEL_1                   ((uint32_t)0x00000200)        /*!< Bit 1 */

/* RTC configuration */
#define  RCC_BDCR_RTCSEL_NOCLOCK             ((uint32_t)0x00000000)        /*!< No clock */
#define  RCC_BDCR_RTCSEL_LSE                 ((uint32_t)0x00000100)        /*!< LSE oscillator clock used as RTC clock */
#define  RCC_BDCR_RTCSEL_LSI                 ((uint32_t)0x00000200)        /*!< LSI oscillator clock used as RTC clock */
#define  RCC_BDCR_RTCSEL_HSE                 ((uint32_t)0x00000300)        /*!< HSE oscillator clock divided by 32 used as RTC clock */

#define  RCC_BDCR_RTCEN                      ((uint32_t)0x00008000)        /*!< RTC clock enable */
#define  RCC_BDCR_BDRST                      ((uint32_t)0x00010000)        /*!< Backup domain software reset  */

/*******************  Bit definition for RCC_CSR register  ********************/  
#define  RCC_CSR_LSION                       ((uint32_t)0x00000001)        /*!< Internal Low Speed oscillator enable */
#define  RCC_CSR_LSIRDY                      ((uint32_t)0x00000002)        /*!< Internal Low Speed oscillator Ready */
#define  RCC_CSR_V18PWRRSTF                  ((uint32_t)0x00800000)        /*!< V1.8 power domain reset flag */
#define  RCC_CSR_RMVF                        ((uint32_t)0x01000000)        /*!< Remove reset flag */
#define  RCC_CSR_OBLRSTF                     ((uint32_t)0x02000000)        /*!< OBL reset flag */
#define  RCC_CSR_PINRSTF                     ((uint32_t)0x04000000)        /*!< PIN reset flag */
#define  RCC_CSR_PORRSTF                     ((uint32_t)0x08000000)        /*!< POR/PDR reset flag */
#define  RCC_CSR_SFTRSTF                     ((uint32_t)0x10000000)        /*!< Software Reset flag */
#define  RCC_CSR_IWDGRSTF                    ((uint32_t)0x20000000)        /*!< Independent Watchdog reset flag */
#define  RCC_CSR_WWDGRSTF                    ((uint32_t)0x40000000)        /*!< Window watchdog reset flag */
#define  RCC_CSR_LPWRRSTF                    ((uint32_t)0x80000000)        /*!< Low-Power reset flag */

/* Old Bit definition maintained for legacy purpose */
#define  RCC_CSR_OBL                         RCC_CSR_OBLRSTF        /*!< OBL reset flag */
/*******************  Bit definition for RCC_AHBRSTR register  ****************/
#define  RCC_AHBRSTR_GPIOARST                ((uint32_t)0x00020000)         /*!< GPIOA clock reset */
#define  RCC_AHBRSTR_GPIOBRST                ((uint32_t)0x00040000)         /*!< GPIOB clock reset */
#define  RCC_AHBRSTR_GPIOCRST                ((uint32_t)0x00080000)         /*!< GPIOC clock reset */
#define  RCC_AHBRSTR_GPIODRST                ((uint32_t)0x00010000)         /*!< GPIOD clock reset */
#define  RCC_AHBRSTR_GPIOERST                ((uint32_t)0x00020000)         /*!< GPIOE clock reset */
#define  RCC_AHBRSTR_GPIOFRST                ((uint32_t)0x00040000)         /*!< GPIOF clock reset */
#define  RCC_AHBRSTR_TSCRST                  ((uint32_t)0x00100000)         /*!< TS clock reset */

/* Old Bit definition maintained for legacy purpose */
#define  RCC_AHBRSTR_TSRST                   RCC_AHBRSTR_TSCRST         /*!< TS clock reset */

/*******************  Bit definition for RCC_CFGR2 register  ******************/
/* PREDIV1 configuration */
#define  RCC_CFGR2_PREDIV1                   ((uint32_t)0x0000000F)        /*!< PREDIV1[3:0] bits */
#define  RCC_CFGR2_PREDIV1_0                 ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  RCC_CFGR2_PREDIV1_1                 ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  RCC_CFGR2_PREDIV1_2                 ((uint32_t)0x00000004)        /*!< Bit 2 */
#define  RCC_CFGR2_PREDIV1_3                 ((uint32_t)0x00000008)        /*!< Bit 3 */

#define  RCC_CFGR2_PREDIV1_DIV1              ((uint32_t)0x00000000)        /*!< PREDIV1 input clock not divided */
#define  RCC_CFGR2_PREDIV1_DIV2              ((uint32_t)0x00000001)        /*!< PREDIV1 input clock divided by 2 */
#define  RCC_CFGR2_PREDIV1_DIV3              ((uint32_t)0x00000002)        /*!< PREDIV1 input clock divided by 3 */
#define  RCC_CFGR2_PREDIV1_DIV4              ((uint32_t)0x00000003)        /*!< PREDIV1 input clock divided by 4 */
#define  RCC_CFGR2_PREDIV1_DIV5              ((uint32_t)0x00000004)        /*!< PREDIV1 input clock divided by 5 */
#define  RCC_CFGR2_PREDIV1_DIV6              ((uint32_t)0x00000005)        /*!< PREDIV1 input clock divided by 6 */
#define  RCC_CFGR2_PREDIV1_DIV7              ((uint32_t)0x00000006)        /*!< PREDIV1 input clock divided by 7 */
#define  RCC_CFGR2_PREDIV1_DIV8              ((uint32_t)0x00000007)        /*!< PREDIV1 input clock divided by 8 */
#define  RCC_CFGR2_PREDIV1_DIV9              ((uint32_t)0x00000008)        /*!< PREDIV1 input clock divided by 9 */
#define  RCC_CFGR2_PREDIV1_DIV10             ((uint32_t)0x00000009)        /*!< PREDIV1 input clock divided by 10 */
#define  RCC_CFGR2_PREDIV1_DIV11             ((uint32_t)0x0000000A)        /*!< PREDIV1 input clock divided by 11 */
#define  RCC_CFGR2_PREDIV1_DIV12             ((uint32_t)0x0000000B)        /*!< PREDIV1 input clock divided by 12 */
#define  RCC_CFGR2_PREDIV1_DIV13             ((uint32_t)0x0000000C)        /*!< PREDIV1 input clock divided by 13 */
#define  RCC_CFGR2_PREDIV1_DIV14             ((uint32_t)0x0000000D)        /*!< PREDIV1 input clock divided by 14 */
#define  RCC_CFGR2_PREDIV1_DIV15             ((uint32_t)0x0000000E)        /*!< PREDIV1 input clock divided by 15 */
#define  RCC_CFGR2_PREDIV1_DIV16             ((uint32_t)0x0000000F)        /*!< PREDIV1 input clock divided by 16 */

/*******************  Bit definition for RCC_CFGR3 register  ******************/
#define  RCC_CFGR3_USART1SW                  ((uint32_t)0x00000003)        /*!< USART1SW[1:0] bits */
#define  RCC_CFGR3_USART1SW_0                ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  RCC_CFGR3_USART1SW_1                ((uint32_t)0x00000002)        /*!< Bit 1 */
#define  RCC_CFGR3_I2C1SW                    ((uint32_t)0x00000010)        /*!< I2C1SW bits */
#define  RCC_CFGR3_CECSW                     ((uint32_t)0x00000040)        /*!< CECSW bits */
#define  RCC_CFGR3_USBSW                     ((uint32_t)0x00000080)        /*!< USBSW bits */
#define  RCC_CFGR3_ADCSW                     ((uint32_t)0x00000100)        /*!< ADCSW bits */
#define  RCC_CFGR3_USART2SW                  ((uint32_t)0x00030000)        /*!< USART2SW[1:0] bits */
#define  RCC_CFGR3_USART2SW_0                ((uint32_t)0x00010000)        /*!< Bit 0 */
#define  RCC_CFGR3_USART2SW_1                ((uint32_t)0x00020000)        /*!< Bit 1 */
#define  RCC_CFGR3_USART3SW                  ((uint32_t)0x000C0000)        /*!< USART3SW[1:0] bits */
#define  RCC_CFGR3_USART3SW_0                ((uint32_t)0x00040000)        /*!< Bit 0 */
#define  RCC_CFGR3_USART3SW_1                ((uint32_t)0x00080000)        /*!< Bit 1 */


/*******************  Bit definition for RCC_CR2 register  ********************/
#define  RCC_CR2_HSI14ON                     ((uint32_t)0x00000001)        /*!< Internal High Speed 14MHz clock enable */
#define  RCC_CR2_HSI14RDY                    ((uint32_t)0x00000002)        /*!< Internal High Speed 14MHz clock ready flag */
#define  RCC_CR2_HSI14DIS                    ((uint32_t)0x00000004)        /*!< Internal High Speed 14MHz clock disable */
#define  RCC_CR2_HSI14TRIM                   ((uint32_t)0x000000F8)        /*!< Internal High Speed 14MHz clock trimming */
#define  RCC_CR2_HSI14CAL                    ((uint32_t)0x0000FF00)        /*!< Internal High Speed 14MHz clock Calibration */
#define  RCC_CR2_HSI48ON                     ((uint32_t)0x00010000)        /*!< Internal High Speed 48MHz clock enable */
#define  RCC_CR2_HSI48RDY                    ((uint32_t)0x00020000)        /*!< Internal High Speed 48MHz clock ready flag */
#define  RCC_CR2_HSI48CAL                    ((uint32_t)0xFF000000)        /*!< Internal High Speed 48MHz clock Calibration */


/******************************************************************************/
/*                                                                            */
/*                       General Purpose IOs (GPIO)                           */
/*                                                                            */
/******************************************************************************/


typedef struct
{
  volatile uint32_t MODER;        /*!< GPIO port mode register,                                  Address offset: 0x00 */
  volatile uint16_t OTYPER;       /*!< GPIO port output type register,                           Address offset: 0x04 */
  uint16_t RESERVED0;         /*!< Reserved,                                                                 0x06 */
  volatile uint32_t OSPEEDR;      /*!< GPIO port output speed register,                          Address offset: 0x08 */
  volatile uint32_t PUPDR;        /*!< GPIO port pull-up/pull-down register,                     Address offset: 0x0C */
  volatile uint16_t IDR;          /*!< GPIO port input data register,                            Address offset: 0x10 */
  uint16_t RESERVED1;         /*!< Reserved,                                                                 0x12 */
  volatile uint16_t ODR;          /*!< GPIO port output data register,                           Address offset: 0x14 */
  uint16_t RESERVED2;         /*!< Reserved,                                                                 0x16 */
  volatile uint32_t BSRR;         /*!< GPIO port bit set/reset registerBSRR,                     Address offset: 0x18 */
  volatile uint32_t LCKR;         /*!< GPIO port configuration lock register,                    Address offset: 0x1C */
  volatile uint32_t AFR[2];       /*!< GPIO alternate function low register,                Address offset: 0x20-0x24 */
  volatile uint16_t BRR;          /*!< GPIO bit reset register,                                  Address offset: 0x28 */
  uint16_t RESERVED3;         /*!< Reserved,                                                                 0x2A */
}GPIO_TypeDef;

extern GPIO_TypeDef reg_sim_GPIO;

#define GPIOA (&reg_sim_GPIO)
#define GPIOB (&reg_sim_GPIO)
#define GPIOC (&reg_sim_GPIO)
#define GPIOD (&reg_sim_GPIO)

/******************************************************************************/
/*                                                                            */
/*                       Real Time Clock (RTC)                                */
/*                                                                            */
/******************************************************************************/

typedef struct
{                           
  volatile uint32_t TR;         /*!< RTC time register,                                        Address offset: 0x00 */
  volatile uint32_t DR;         /*!< RTC date register,                                        Address offset: 0x04 */
  volatile uint32_t CR;         /*!< RTC control register,                                     Address offset: 0x08 */
  volatile uint32_t ISR;        /*!< RTC initialization and status register,                   Address offset: 0x0C */
  volatile uint32_t PRER;       /*!< RTC prescaler register,                                   Address offset: 0x10 */
  volatile uint32_t WUTR;       /*!< RTC wakeup timer register,(only for STM32F072 devices)    Address offset: 0x14 */
       uint32_t RESERVED1;  /*!< Reserved,                                                 Address offset: 0x18 */
  volatile uint32_t ALRMAR;     /*!< RTC alarm A register,                                     Address offset: 0x1C */
       uint32_t RESERVED2;  /*!< Reserved,                                                 Address offset: 0x20 */
  volatile uint32_t WPR;        /*!< RTC write protection register,                            Address offset: 0x24 */
  volatile uint32_t SSR;        /*!< RTC sub second register,                                  Address offset: 0x28 */
  volatile uint32_t SHIFTR;     /*!< RTC shift control register,                               Address offset: 0x2C */
  volatile uint32_t TSTR;       /*!< RTC time stamp time register,                             Address offset: 0x30 */
  volatile uint32_t TSDR;       /*!< RTC time stamp date register,                             Address offset: 0x34 */
  volatile uint32_t TSSSR;      /*!< RTC time-stamp sub second register,                       Address offset: 0x38 */
  volatile uint32_t CALR;       /*!< RTC calibration register,                                 Address offset: 0x3C */
  volatile uint32_t TAFCR;      /*!< RTC tamper and alternate function configuration register, Address offset: 0x40 */
  volatile uint32_t ALRMASSR;   /*!< RTC alarm A sub second register,                          Address offset: 0x44 */
       uint32_t RESERVED3;  /*!< Reserved,                                                 Address offset: 0x48 */
       uint32_t RESERVED4;  /*!< Reserved,                                                 Address offset: 0x4C */
  volatile uint32_t BKP0R;      /*!< RTC backup register 0,                                    Address offset: 0x50 */
  volatile uint32_t BKP1R;      /*!< RTC backup register 1,                                    Address offset: 0x54 */
  volatile uint32_t BKP2R;      /*!< RTC backup register 2,                                    Address offset: 0x58 */
  volatile uint32_t BKP3R;      /*!< RTC backup register 3,                                    Address offset: 0x5C */
  volatile uint32_t BKP4R;      /*!< RTC backup register 4,                                    Address offset: 0x60 */
} RTC_TypeDef;

extern RTC_TypeDef reg_sim_RTC;
#define RTC (&reg_sim_RTC)


/********************  Bits definition for RTC_TR register  *******************/
#define RTC_TR_PM                            ((uint32_t)0x00400000)
#define RTC_TR_HT                            ((uint32_t)0x00300000)        
#define RTC_TR_HT_0                          ((uint32_t)0x00100000)        
#define RTC_TR_HT_1                          ((uint32_t)0x00200000)        
#define RTC_TR_HU                            ((uint32_t)0x000F0000)        
#define RTC_TR_HU_0                          ((uint32_t)0x00010000)        
#define RTC_TR_HU_1                          ((uint32_t)0x00020000)        
#define RTC_TR_HU_2                          ((uint32_t)0x00040000)        
#define RTC_TR_HU_3                          ((uint32_t)0x00080000)        
#define RTC_TR_MNT                           ((uint32_t)0x00007000)        
#define RTC_TR_MNT_0                         ((uint32_t)0x00001000)        
#define RTC_TR_MNT_1                         ((uint32_t)0x00002000)        
#define RTC_TR_MNT_2                         ((uint32_t)0x00004000)        
#define RTC_TR_MNU                           ((uint32_t)0x00000F00)        
#define RTC_TR_MNU_0                         ((uint32_t)0x00000100)        
#define RTC_TR_MNU_1                         ((uint32_t)0x00000200)        
#define RTC_TR_MNU_2                         ((uint32_t)0x00000400)        
#define RTC_TR_MNU_3                         ((uint32_t)0x00000800)        
#define RTC_TR_ST                            ((uint32_t)0x00000070)        
#define RTC_TR_ST_0                          ((uint32_t)0x00000010)        
#define RTC_TR_ST_1                          ((uint32_t)0x00000020)        
#define RTC_TR_ST_2                          ((uint32_t)0x00000040)        
#define RTC_TR_SU                            ((uint32_t)0x0000000F)        
#define RTC_TR_SU_0                          ((uint32_t)0x00000001)        
#define RTC_TR_SU_1                          ((uint32_t)0x00000002)        
#define RTC_TR_SU_2                          ((uint32_t)0x00000004)        
#define RTC_TR_SU_3                          ((uint32_t)0x00000008)        

/********************  Bits definition for RTC_DR register  *******************/
#define RTC_DR_YT                            ((uint32_t)0x00F00000)        
#define RTC_DR_YT_0                          ((uint32_t)0x00100000)        
#define RTC_DR_YT_1                          ((uint32_t)0x00200000)        
#define RTC_DR_YT_2                          ((uint32_t)0x00400000)        
#define RTC_DR_YT_3                          ((uint32_t)0x00800000)        
#define RTC_DR_YU                            ((uint32_t)0x000F0000)        
#define RTC_DR_YU_0                          ((uint32_t)0x00010000)        
#define RTC_DR_YU_1                          ((uint32_t)0x00020000)        
#define RTC_DR_YU_2                          ((uint32_t)0x00040000)        
#define RTC_DR_YU_3                          ((uint32_t)0x00080000)        
#define RTC_DR_WDU                           ((uint32_t)0x0000E000)        
#define RTC_DR_WDU_0                         ((uint32_t)0x00002000)        
#define RTC_DR_WDU_1                         ((uint32_t)0x00004000)        
#define RTC_DR_WDU_2                         ((uint32_t)0x00008000)        
#define RTC_DR_MT                            ((uint32_t)0x00001000)        
#define RTC_DR_MU                            ((uint32_t)0x00000F00)        
#define RTC_DR_MU_0                          ((uint32_t)0x00000100)        
#define RTC_DR_MU_1                          ((uint32_t)0x00000200)        
#define RTC_DR_MU_2                          ((uint32_t)0x00000400)        
#define RTC_DR_MU_3                          ((uint32_t)0x00000800)        
#define RTC_DR_DT                            ((uint32_t)0x00000030)        
#define RTC_DR_DT_0                          ((uint32_t)0x00000010)        
#define RTC_DR_DT_1                          ((uint32_t)0x00000020)        
#define RTC_DR_DU                            ((uint32_t)0x0000000F)        
#define RTC_DR_DU_0                          ((uint32_t)0x00000001)        
#define RTC_DR_DU_1                          ((uint32_t)0x00000002)        
#define RTC_DR_DU_2                          ((uint32_t)0x00000004)        
#define RTC_DR_DU_3                          ((uint32_t)0x00000008)        

/********************  Bits definition for RTC_CR register  *******************/
#define RTC_CR_COE                           ((uint32_t)0x00800000)        
#define RTC_CR_OSEL                          ((uint32_t)0x00600000)        
#define RTC_CR_OSEL_0                        ((uint32_t)0x00200000)        
#define RTC_CR_OSEL_1                        ((uint32_t)0x00400000)        
#define RTC_CR_POL                           ((uint32_t)0x00100000)        
#define RTC_CR_COSEL                         ((uint32_t)0x00080000)        
#define RTC_CR_BKP                           ((uint32_t)0x00040000)        
#define RTC_CR_SUB1H                         ((uint32_t)0x00020000)        
#define RTC_CR_ADD1H                         ((uint32_t)0x00010000)        
#define RTC_CR_TSIE                          ((uint32_t)0x00008000)        
#define RTC_CR_WUTIE                         ((uint32_t)0x00004000)
#define RTC_CR_ALRAIE                        ((uint32_t)0x00001000)        
#define RTC_CR_TSE                           ((uint32_t)0x00000800)        
#define RTC_CR_WUTE                          ((uint32_t)0x00000400)        
#define RTC_CR_ALRAE                         ((uint32_t)0x00000100)        
#define RTC_CR_FMT                           ((uint32_t)0x00000040)        
#define RTC_CR_BYPSHAD                       ((uint32_t)0x00000020)        
#define RTC_CR_REFCKON                       ((uint32_t)0x00000010)        
#define RTC_CR_TSEDGE                        ((uint32_t)0x00000008)        
#define RTC_CR_WUCKSEL                       ((uint32_t)0x00000007)        
#define RTC_CR_WUCKSEL_0                     ((uint32_t)0x00000001)        
#define RTC_CR_WUCKSEL_1                     ((uint32_t)0x00000002)        
#define RTC_CR_WUCKSEL_2                     ((uint32_t)0x00000004)        

/* Old bit definition maintained for legacy purpose */
#define RTC_CR_BCK                           RTC_CR_BKP
#define RTC_CR_CALSEL                        RTC_CR_COSEL

/********************  Bits definition for RTC_ISR register  ******************/
#define RTC_ISR_RECALPF                      ((uint32_t)0x00010000)        
#define RTC_ISR_TAMP3F                       ((uint32_t)0x00008000)        
#define RTC_ISR_TAMP2F                       ((uint32_t)0x00004000)        
#define RTC_ISR_TAMP1F                       ((uint32_t)0x00002000)        
#define RTC_ISR_TSOVF                        ((uint32_t)0x00001000)        
#define RTC_ISR_TSF                          ((uint32_t)0x00000800)        
#define RTC_ISR_WUTF                         ((uint32_t)0x00000400)        
#define RTC_ISR_ALRAF                        ((uint32_t)0x00000100)        
#define RTC_ISR_INIT                         ((uint32_t)0x00000080)        
#define RTC_ISR_INITF                        ((uint32_t)0x00000040)        
#define RTC_ISR_RSF                          ((uint32_t)0x00000020)        
#define RTC_ISR_INITS                        ((uint32_t)0x00000010)        
#define RTC_ISR_SHPF                         ((uint32_t)0x00000008)        
#define RTC_ISR_WUTWF                        ((uint32_t)0x00000004)        
#define RTC_ISR_ALRAWF                       ((uint32_t)0x00000001)        

/********************  Bits definition for RTC_PRER register  *****************/
#define RTC_PRER_PREDIV_A                    ((uint32_t)0x007F0000)        
#define RTC_PRER_PREDIV_S                    ((uint32_t)0x00007FFF)        

/********************  Bits definition for RTC_WUTR register  *****************/
#define RTC_WUTR_WUT                         ((uint32_t)0x0000FFFF)

/********************  Bits definition for RTC_ALRMAR register  ***************/
#define RTC_ALRMAR_MSK4                      ((uint32_t)0x80000000)        
#define RTC_ALRMAR_WDSEL                     ((uint32_t)0x40000000)        
#define RTC_ALRMAR_DT                        ((uint32_t)0x30000000)        
#define RTC_ALRMAR_DT_0                      ((uint32_t)0x10000000)        
#define RTC_ALRMAR_DT_1                      ((uint32_t)0x20000000)        
#define RTC_ALRMAR_DU                        ((uint32_t)0x0F000000)        
#define RTC_ALRMAR_DU_0                      ((uint32_t)0x01000000)        
#define RTC_ALRMAR_DU_1                      ((uint32_t)0x02000000)        
#define RTC_ALRMAR_DU_2                      ((uint32_t)0x04000000)        
#define RTC_ALRMAR_DU_3                      ((uint32_t)0x08000000)        
#define RTC_ALRMAR_MSK3                      ((uint32_t)0x00800000)        
#define RTC_ALRMAR_PM                        ((uint32_t)0x00400000)        
#define RTC_ALRMAR_HT                        ((uint32_t)0x00300000)        
#define RTC_ALRMAR_HT_0                      ((uint32_t)0x00100000)        
#define RTC_ALRMAR_HT_1                      ((uint32_t)0x00200000)        
#define RTC_ALRMAR_HU                        ((uint32_t)0x000F0000)        
#define RTC_ALRMAR_HU_0                      ((uint32_t)0x00010000)        
#define RTC_ALRMAR_HU_1                      ((uint32_t)0x00020000)        
#define RTC_ALRMAR_HU_2                      ((uint32_t)0x00040000)        
#define RTC_ALRMAR_HU_3                      ((uint32_t)0x00080000)        
#define RTC_ALRMAR_MSK2                      ((uint32_t)0x00008000)        
#define RTC_ALRMAR_MNT                       ((uint32_t)0x00007000)        
#define RTC_ALRMAR_MNT_0                     ((uint32_t)0x00001000)        
#define RTC_ALRMAR_MNT_1                     ((uint32_t)0x00002000)        
#define RTC_ALRMAR_MNT_2                     ((uint32_t)0x00004000)        
#define RTC_ALRMAR_MNU                       ((uint32_t)0x00000F00)        
#define RTC_ALRMAR_MNU_0                     ((uint32_t)0x00000100)        
#define RTC_ALRMAR_MNU_1                     ((uint32_t)0x00000200)        
#define RTC_ALRMAR_MNU_2                     ((uint32_t)0x00000400)        
#define RTC_ALRMAR_MNU_3                     ((uint32_t)0x00000800)        
#define RTC_ALRMAR_MSK1                      ((uint32_t)0x00000080)        
#define RTC_ALRMAR_ST                        ((uint32_t)0x00000070)        
#define RTC_ALRMAR_ST_0                      ((uint32_t)0x00000010)        
#define RTC_ALRMAR_ST_1                      ((uint32_t)0x00000020)        
#define RTC_ALRMAR_ST_2                      ((uint32_t)0x00000040)        
#define RTC_ALRMAR_SU                        ((uint32_t)0x0000000F)        
#define RTC_ALRMAR_SU_0                      ((uint32_t)0x00000001)        
#define RTC_ALRMAR_SU_1                      ((uint32_t)0x00000002)        
#define RTC_ALRMAR_SU_2                      ((uint32_t)0x00000004)        
#define RTC_ALRMAR_SU_3                      ((uint32_t)0x00000008)        

/********************  Bits definition for RTC_WPR register  ******************/
#define RTC_WPR_KEY                          ((uint32_t)0x000000FF)        

/********************  Bits definition for RTC_SSR register  ******************/
#define RTC_SSR_SS                           ((uint32_t)0x0003FFFF)        

/********************  Bits definition for RTC_SHIFTR register  ***************/
#define RTC_SHIFTR_SUBFS                     ((uint32_t)0x00007FFF)        
#define RTC_SHIFTR_ADD1S                     ((uint32_t)0x80000000)        

/********************  Bits definition for RTC_TSTR register  *****************/
#define RTC_TSTR_PM                          ((uint32_t)0x00400000)        
#define RTC_TSTR_HT                          ((uint32_t)0x00300000)        
#define RTC_TSTR_HT_0                        ((uint32_t)0x00100000)        
#define RTC_TSTR_HT_1                        ((uint32_t)0x00200000)        
#define RTC_TSTR_HU                          ((uint32_t)0x000F0000)        
#define RTC_TSTR_HU_0                        ((uint32_t)0x00010000)        
#define RTC_TSTR_HU_1                        ((uint32_t)0x00020000)        
#define RTC_TSTR_HU_2                        ((uint32_t)0x00040000)        
#define RTC_TSTR_HU_3                        ((uint32_t)0x00080000)        
#define RTC_TSTR_MNT                         ((uint32_t)0x00007000)        
#define RTC_TSTR_MNT_0                       ((uint32_t)0x00001000)        
#define RTC_TSTR_MNT_1                       ((uint32_t)0x00002000)        
#define RTC_TSTR_MNT_2                       ((uint32_t)0x00004000)        
#define RTC_TSTR_MNU                         ((uint32_t)0x00000F00)        
#define RTC_TSTR_MNU_0                       ((uint32_t)0x00000100)        
#define RTC_TSTR_MNU_1                       ((uint32_t)0x00000200)        
#define RTC_TSTR_MNU_2                       ((uint32_t)0x00000400)        
#define RTC_TSTR_MNU_3                       ((uint32_t)0x00000800)        
#define RTC_TSTR_ST                          ((uint32_t)0x00000070)        
#define RTC_TSTR_ST_0                        ((uint32_t)0x00000010)        
#define RTC_TSTR_ST_1                        ((uint32_t)0x00000020)        
#define RTC_TSTR_ST_2                        ((uint32_t)0x00000040)        
#define RTC_TSTR_SU                          ((uint32_t)0x0000000F)        
#define RTC_TSTR_SU_0                        ((uint32_t)0x00000001)        
#define RTC_TSTR_SU_1                        ((uint32_t)0x00000002)        
#define RTC_TSTR_SU_2                        ((uint32_t)0x00000004)        
#define RTC_TSTR_SU_3                        ((uint32_t)0x00000008)        

/********************  Bits definition for RTC_TSDR register  *****************/
#define RTC_TSDR_WDU                         ((uint32_t)0x0000E000)        
#define RTC_TSDR_WDU_0                       ((uint32_t)0x00002000)        
#define RTC_TSDR_WDU_1                       ((uint32_t)0x00004000)        
#define RTC_TSDR_WDU_2                       ((uint32_t)0x00008000)        
#define RTC_TSDR_MT                          ((uint32_t)0x00001000)        
#define RTC_TSDR_MU                          ((uint32_t)0x00000F00)        
#define RTC_TSDR_MU_0                        ((uint32_t)0x00000100)        
#define RTC_TSDR_MU_1                        ((uint32_t)0x00000200)        
#define RTC_TSDR_MU_2                        ((uint32_t)0x00000400)        
#define RTC_TSDR_MU_3                        ((uint32_t)0x00000800)        
#define RTC_TSDR_DT                          ((uint32_t)0x00000030)        
#define RTC_TSDR_DT_0                        ((uint32_t)0x00000010)        
#define RTC_TSDR_DT_1                        ((uint32_t)0x00000020)        
#define RTC_TSDR_DU                          ((uint32_t)0x0000000F)        
#define RTC_TSDR_DU_0                        ((uint32_t)0x00000001)        
#define RTC_TSDR_DU_1                        ((uint32_t)0x00000002)        
#define RTC_TSDR_DU_2                        ((uint32_t)0x00000004)        
#define RTC_TSDR_DU_3                        ((uint32_t)0x00000008)        

/********************  Bits definition for RTC_TSSSR register  ****************/
#define RTC_TSSSR_SS                         ((uint32_t)0x0003FFFF)

/********************  Bits definition for RTC_CALR register  ******************/
#define RTC_CALR_CALP                         ((uint32_t)0x00008000)        
#define RTC_CALR_CALW8                        ((uint32_t)0x00004000)        
#define RTC_CALR_CALW16                       ((uint32_t)0x00002000)        
#define RTC_CALR_CALM                         ((uint32_t)0x000001FF)        
#define RTC_CALR_CALM_0                       ((uint32_t)0x00000001)        
#define RTC_CALR_CALM_1                       ((uint32_t)0x00000002)        
#define RTC_CALR_CALM_2                       ((uint32_t)0x00000004)        
#define RTC_CALR_CALM_3                       ((uint32_t)0x00000008)        
#define RTC_CALR_CALM_4                       ((uint32_t)0x00000010)        
#define RTC_CALR_CALM_5                       ((uint32_t)0x00000020)        
#define RTC_CALR_CALM_6                       ((uint32_t)0x00000040)        
#define RTC_CALR_CALM_7                       ((uint32_t)0x00000080)        
#define RTC_CALR_CALM_8                       ((uint32_t)0x00000100)

/* Old Bits definition for RTC_CAL register maintained for legacy purpose */
#define RTC_CAL_CALP                         RTC_CALR_CALP  
#define RTC_CAL_CALW8                        RTC_CALR_CALW8 
#define RTC_CAL_CALW16                       RTC_CALR_CALW16
#define RTC_CAL_CALM                         RTC_CALR_CALM  
#define RTC_CAL_CALM_0                       RTC_CALR_CALM_0
#define RTC_CAL_CALM_1                       RTC_CALR_CALM_1
#define RTC_CAL_CALM_2                       RTC_CALR_CALM_2
#define RTC_CAL_CALM_3                       RTC_CALR_CALM_3
#define RTC_CAL_CALM_4                       RTC_CALR_CALM_4
#define RTC_CAL_CALM_5                       RTC_CALR_CALM_5
#define RTC_CAL_CALM_6                       RTC_CALR_CALM_6
#define RTC_CAL_CALM_7                       RTC_CALR_CALM_7
#define RTC_CAL_CALM_8                       RTC_CALR_CALM_8

/********************  Bits definition for RTC_TAFCR register  ****************/
#define RTC_TAFCR_PC15MODE                   ((uint32_t)0x00800000)
#define RTC_TAFCR_PC15VALUE                  ((uint32_t)0x00400000)
#define RTC_TAFCR_PC14MODE                   ((uint32_t)0x00200000)
#define RTC_TAFCR_PC14VALUE                  ((uint32_t)0x00100000)
#define RTC_TAFCR_PC13MODE                   ((uint32_t)0x00080000)
#define RTC_TAFCR_PC13VALUE                  ((uint32_t)0x00040000)        
#define RTC_TAFCR_TAMPPUDIS                  ((uint32_t)0x00008000)        
#define RTC_TAFCR_TAMPPRCH                   ((uint32_t)0x00006000)        
#define RTC_TAFCR_TAMPPRCH_0                 ((uint32_t)0x00002000)        
#define RTC_TAFCR_TAMPPRCH_1                 ((uint32_t)0x00004000)        
#define RTC_TAFCR_TAMPFLT                    ((uint32_t)0x00001800)        
#define RTC_TAFCR_TAMPFLT_0                  ((uint32_t)0x00000800)        
#define RTC_TAFCR_TAMPFLT_1                  ((uint32_t)0x00001000)        
#define RTC_TAFCR_TAMPFREQ                   ((uint32_t)0x00000700)        
#define RTC_TAFCR_TAMPFREQ_0                 ((uint32_t)0x00000100)        
#define RTC_TAFCR_TAMPFREQ_1                 ((uint32_t)0x00000200)        
#define RTC_TAFCR_TAMPFREQ_2                 ((uint32_t)0x00000400)        
#define RTC_TAFCR_TAMPTS                     ((uint32_t)0x00000080)        
#define RTC_TAFCR_TAMP3EDGE                  ((uint32_t)0x00000040)        
#define RTC_TAFCR_TAMP3E                     ((uint32_t)0x00000020)        
#define RTC_TAFCR_TAMP2EDGE                  ((uint32_t)0x00000010)        
#define RTC_TAFCR_TAMP2E                     ((uint32_t)0x00000008)        
#define RTC_TAFCR_TAMPIE                     ((uint32_t)0x00000004)        
#define RTC_TAFCR_TAMP1TRG                   ((uint32_t)0x00000002)        
#define RTC_TAFCR_TAMP1E                     ((uint32_t)0x00000001)        

/* Old bit definition maintained for legacy purpose */
#define RTC_TAFCR_ALARMOUTTYPE               RTC_TAFCR_PC13VALUE

/********************  Bits definition for RTC_ALRMASSR register  *************/
#define RTC_ALRMASSR_MASKSS                  ((uint32_t)0x0F000000)        
#define RTC_ALRMASSR_MASKSS_0                ((uint32_t)0x01000000)        
#define RTC_ALRMASSR_MASKSS_1                ((uint32_t)0x02000000)        
#define RTC_ALRMASSR_MASKSS_2                ((uint32_t)0x04000000)        
#define RTC_ALRMASSR_MASKSS_3                ((uint32_t)0x08000000)        
#define RTC_ALRMASSR_SS                      ((uint32_t)0x00007FFF)        

/********************  Bits definition for RTC_BKP0R register  ****************/
#define RTC_BKP0R                            ((uint32_t)0xFFFFFFFF)        

/********************  Bits definition for RTC_BKP1R register  ****************/
#define RTC_BKP1R                            ((uint32_t)0xFFFFFFFF)        

/********************  Bits definition for RTC_BKP2R register  ****************/
#define RTC_BKP2R                            ((uint32_t)0xFFFFFFFF)        

/********************  Bits definition for RTC_BKP3R register  ****************/
#define RTC_BKP3R                            ((uint32_t)0xFFFFFFFF)        

/********************  Bits definition for RTC_BKP4R register  ****************/
#define RTC_BKP4R                            ((uint32_t)0xFFFFFFFF)


/******************************************************************************/
/*                                                                            */
/*                          Power Control (PWR)                               */
/*                                                                            */
/******************************************************************************/

typedef struct
{
  volatile uint32_t CR;   /*!< PWR power control register,        Address offset: 0x00 */
  volatile uint32_t CSR;  /*!< PWR power control/status register, Address offset: 0x04 */
} PWR_TypeDef;

extern PWR_TypeDef reg_sim_PWR;
#define PWR (&reg_sim_PWR)

/********************  Bit definition for PWR_CR register  ********************/
#define  PWR_CR_LPDS                         ((uint16_t)0x0001)     /*!< Low-power deepsleep/sleep */
#define  PWR_CR_PDDS                         ((uint16_t)0x0002)     /*!< Power Down Deepsleep */
#define  PWR_CR_CWUF                         ((uint16_t)0x0004)     /*!< Clear Wakeup Flag */
#define  PWR_CR_CSBF                         ((uint16_t)0x0008)     /*!< Clear Standby Flag */
#define  PWR_CR_PVDE                         ((uint16_t)0x0010)     /*!< Power Voltage Detector Enable */

#define  PWR_CR_PLS                          ((uint16_t)0x00E0)     /*!< PLS[2:0] bits (PVD Level Selection) */
#define  PWR_CR_PLS_0                        ((uint16_t)0x0020)     /*!< Bit 0 */
#define  PWR_CR_PLS_1                        ((uint16_t)0x0040)     /*!< Bit 1 */
#define  PWR_CR_PLS_2                        ((uint16_t)0x0080)     /*!< Bit 2 */
/* PVD level configuration */
#define  PWR_CR_PLS_LEV0                     ((uint16_t)0x0000)     /*!< PVD level 0 */
#define  PWR_CR_PLS_LEV1                     ((uint16_t)0x0020)     /*!< PVD level 1 */
#define  PWR_CR_PLS_LEV2                     ((uint16_t)0x0040)     /*!< PVD level 2 */
#define  PWR_CR_PLS_LEV3                     ((uint16_t)0x0060)     /*!< PVD level 3 */
#define  PWR_CR_PLS_LEV4                     ((uint16_t)0x0080)     /*!< PVD level 4 */
#define  PWR_CR_PLS_LEV5                     ((uint16_t)0x00A0)     /*!< PVD level 5 */
#define  PWR_CR_PLS_LEV6                     ((uint16_t)0x00C0)     /*!< PVD level 6 */
#define  PWR_CR_PLS_LEV7                     ((uint16_t)0x00E0)     /*!< PVD level 7 */

#define  PWR_CR_DBP                          ((uint16_t)0x0100)     /*!< Disable Backup Domain write protection */

/* Old Bit definition maintained for legacy purpose ****/
#define  PWR_CR_LPSDSR                       PWR_CR_LPDS     /*!< Low-power deepsleep */

/*******************  Bit definition for PWR_CSR register  ********************/
#define  PWR_CSR_WUF                         ((uint16_t)0x0001)     /*!< Wakeup Flag */
#define  PWR_CSR_SBF                         ((uint16_t)0x0002)     /*!< Standby Flag */
#define  PWR_CSR_PVDO                        ((uint16_t)0x0004)     /*!< PVD Output */
#define  PWR_CSR_VREFINTRDY                  ((uint16_t)0x0008)     /*!< Internal voltage reference (VREFINT) ready */

#define  PWR_CSR_EWUP1                       ((uint16_t)0x0100)     /*!< Enable WKUP pin 1 */
#define  PWR_CSR_EWUP2                       ((uint16_t)0x0200)     /*!< Enable WKUP pin 2 */
#define  PWR_CSR_EWUP3                       ((uint16_t)0x0400)     /*!< Enable WKUP pin 3 */
#define  PWR_CSR_EWUP4                       ((uint16_t)0x0800)     /*!< Enable WKUP pin 4 */
#define  PWR_CSR_EWUP5                       ((uint16_t)0x1000)     /*!< Enable WKUP pin 5 */
#define  PWR_CSR_EWUP6                       ((uint16_t)0x2000)     /*!< Enable WKUP pin 6 */
#define  PWR_CSR_EWUP7                       ((uint16_t)0x4000)     /*!< Enable WKUP pin 7 */
#define  PWR_CSR_EWUP8                       ((uint16_t)0x8000)     /*!< Enable WKUP pin 8 */

/* Old Bit definition maintained for legacy purpose ****/
#define  PWR_CSR_VREFINTRDYF                 PWR_CSR_VREFINTRDY     /*!< Internal voltage reference (VREFINT) ready flag */

#endif