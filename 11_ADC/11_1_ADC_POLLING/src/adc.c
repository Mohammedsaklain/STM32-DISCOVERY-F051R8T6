#include "adc.h"
#include "custom.h"

void ADC_Init(void){
    ADC1->CR|= ADC_CR_ADCAL;                /* Start ADC calibration */
    while(((ADC1->CR)&(ADC_CR_ADCAL))!=0);  /* Wait for hardware to clear ADCAL after calibration */

    ADC1->CR &= ~ADC_CR_ADEN;               /* Disable ADC */
    ADC1->CFGR1 = 0;                        /* Right aligned, 12 bit resolution*/
    ADC1->CFGR2 = 0;
    ADC1->CHSELR |= ADC_CHSELR_CHSEL1;      /* Select the Channel 1- PA1 */
    ADC1->CR |= ADC_CR_ADEN;                /* Enable ADC*/
}

uint16_t ADC_Read(void){
    ADC1->CR |= ADC_CR_ADSTART;             /* Start ADC conversion */
    while(!((ADC1->ISR)&(ADC_ISR_EOSMP)));  /* End of sampling, wait for sampling to be over */
    return (ADC1->DR);                      /* Return conversion result */
}