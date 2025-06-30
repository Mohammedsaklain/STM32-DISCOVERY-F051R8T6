#include "custom.h"
#include "low_pwr_md.h"

/* This function is declaration gives distinction between WFI & WFE*/
void Low_Power_Mode(void){
#ifdef SLEEP_MODE
    #ifdef WFI_LPM
        SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
        __WFI();		// Wait for Interrupt(any Intr)
    #else
        __SEV();    // Set the event register
        __WFE();    // clear event register
        __WFE();    // Now wait here until a new event occurs
    #endif
#endif
#ifdef STOP_MODE
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;  // Deep Sleep Mode
    PWR->CR &= ~PWR_CR_PDDS;            // Enter Stop mode when the CPU enters Deepsleep
    PWR->CR |=  PWR_CR_LPDS;            // Voltage regulator on during Stop mode
    #ifdef WFI_LPM
        SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
        __WFI();		// Wait for Interrupt(any Intr)
    #else
        __SEV();    // Set the event register
        __WFE();    // clear event register
        __WFE();    // Now wait here until a new event occurs
    #endif
#endif
#ifdef STANDBY_MODE
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;      // Set to Deep Sleep Mode
    PWR->CR |=  PWR_CR_PDDS;                // Enter Standby mode when the CPU enters Deepsleep
    PWR->CSR |= PWR_CSR_EWUP1;              // Select the Wake Up pin - PA0
    PWR->CR |= PWR_CR_CWUF;                 // Clear WUF - Wake up flag
    PWR->CSR&= ~PWR_CSR_WUF;                // it shows wether wakeup event was occured previously, it can be cleared directly or using CWUF flag in PWR->CR 
    PWR->CR |= PWR_CR_CSBF;                 // Clear standby flag
    #ifdef WFI_LPM
        SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
        __WFI();		// Wait for Interrupt(any Intr)
    #else
        __SEV();    // Set the event register
        __WFE();    // clear event register
        __WFE();    // Now wait here until a new event occurs
    #endif
#endif
}
