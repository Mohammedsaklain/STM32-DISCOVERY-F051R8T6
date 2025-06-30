#include "main.h"
#include <stdint.h>

#ifndef HOST_UNIT_TEST
	int main(){
		UART_Init();
		//uint16_t a = 0;
		while(1)
		{
		//	MS_printf("Hello from main %d\r\n",a);
		//	for(int i=0;i<800000;i++){}
		//	a++;
		MS_printf("A\r\n");
		for(int i=0;i<50000;i++){
			int j =0;
			int k=j;
		}
		for(int i=0;i<50000;i++){
			int l=0;
			int m =l;
		}
		for(int i=0;i<50000;i++){
			int n=0;
			int o = n;
		}
		for(int i=0;i<50000;i++);
		}
		return 0;
	}	
#else	/* In origin, There should not be any infinite loops present*/
	int origin(){
		RTC_Start();
		return 0;
	}
#endif
