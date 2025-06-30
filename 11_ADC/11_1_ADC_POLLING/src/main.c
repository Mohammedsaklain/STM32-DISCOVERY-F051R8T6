#include "custom.h"
#include "gpio_dr.h"
#include "uart.h"
#include "adc.h"

#ifndef HOST_UNIT_TEST
	float V;
	int main(){
		UART_Init();
		ADC_Init();
		
		GPIOA->MODER &= ~(3<<2);
		GPIOA->MODER |=  (3<<2);	// Analog Mode - PA1
		uint16_t F_ADC_Val;
		uint32_t ADC_VIN = 3;
		uint32_t RESOLUTION_12 = 4096;
		while(1)
		{
			F_ADC_Val = ADC_Read();
			V = ((float)ADC_VIN/(float)RESOLUTION_12)*F_ADC_Val;
			print_float(V);
			for(volatile int i=0;i<5000;i++);
		}
		return 0;
	}	
#else	/* In origin, There should not be any infinite loops present*/
	int origin(){
		return 0;
	}
#endif