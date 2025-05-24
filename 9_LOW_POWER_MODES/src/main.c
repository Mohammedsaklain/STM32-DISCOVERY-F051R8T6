#include "main.h"

#ifndef HOST_UNIT_TEST
	int main(){
		UART_Init();
		/* Detect wether we work up from Standby mode*/
		if(PWR->CSR & PWR_CSR_SBF){
			MS_printf("Woke up from STANDBY mode\r\n");
			PWR->CR |= PWR_CR_CSBF;		// Clear Flag
		}
		#ifdef WFI_LPM
			//External_INT_Init();
			Low_Power_Mode();
		#elif WFE_LPM
			External_Event_Init();
		#endif
		while(1)
		{
			#ifdef WFE_LPM
				Low_Power_Mode();
				MS_printf("Ext Int Triggered\r\n");		// When exit from WFE, then string will be shown
			#endif
		}
		return 0;
	}	
#else	/* In origin, There should not be any infinite loops present*/
	int origin(){
		RTC_Start();
		return 0;
	}
#endif
