#include "main.h"

#ifndef HOST_UNIT_TEST
	int main(){
		UART_Init();
		int a = 0;
		while(1)
		{
			MS_printf("Hello from main %d\r\n",a);
			for(int i=0;i<800000;i++){}
			a++;
		}
		return 0;
	}	
#else	/* In origin, There should not be any infinite loops present*/
	int origin(){
		RTC_Start();
		return 0;
	}
#endif
