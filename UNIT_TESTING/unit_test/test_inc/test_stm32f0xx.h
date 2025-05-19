#ifndef TEST_STM32F0XX_H_
#define TEST_STM32F0XX_H_

#include "stdint.h"

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

/********************  RCC  ********************/
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


#endif