#ifndef LOW_PWR_MD_H_
#define LOW_PWR_MD_H_

#undef SLEEP_MODE
#undef STOP_MODE
#undef STANDBY_MODE

#define WFI_LPM     /* Wait for Interrupt for Low Power Mode*/
#undef WFE_LPM    /* Wait for Event for Low Power Mode*/

void Low_Power_Mode(void);

#endif