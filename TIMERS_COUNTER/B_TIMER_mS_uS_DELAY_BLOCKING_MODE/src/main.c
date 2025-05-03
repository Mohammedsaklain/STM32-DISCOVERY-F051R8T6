#include "rcc.h"
#include "gpio.h"
#include "timer.h"

/* Program: 	Custom delay function in mS & uS*/
/* Limitations: Found out that for lesser time period(of 10us) the accuracy decreases*/

int main()
{
	rcc_clock_config();
	gpio_set();
	Timer6_Init();
	while(1)
	{
		GPIOC->ODR |= GPIO_ODR_8;
		//Delay_uS(50);
		Delay_mS(1000);
		GPIOC->ODR &= ~GPIO_ODR_8;
		//Delay_uS(50);
		Delay_mS(1000);
	}
	return 0;
}

