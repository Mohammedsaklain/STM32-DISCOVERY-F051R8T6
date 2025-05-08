#include "rcc.h"
#include "gpio_dr.h"
#include "stm32f0xx.h"
#include "timer_dr.h"



int main()
{
	Gpio_Init(GPIOA,5,AF,NO_PUPD);	//CH1
	Gpio_Af(GPIOA,5,AF2);
	Gpio_Init(GPIOA,1,AF,NO_PUPD);  //CH2
	Gpio_Af(GPIOA,1,AF2);

	Timer_Init(T2,7999,1000,FALSE);
	Timer_Compare_Init(T2,CH1,0);
	Timer_Compare_Init(T2,CH2,50);
	//Timer_PWM_Init(T2,CH1,50); 
	//Timer_PWM_Init(T2,CH2,20);    

	while(1)
	{

	}
	return 0;
}
