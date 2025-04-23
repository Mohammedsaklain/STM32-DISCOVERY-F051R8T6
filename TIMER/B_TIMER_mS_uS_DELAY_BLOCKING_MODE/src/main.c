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
		GPIOC->ODR |= (1<<8);
		Delay_uS(10);
		GPIOC->ODR &= ~(1<<8);
		Delay_uS(10);
	}
	return 0;
}

