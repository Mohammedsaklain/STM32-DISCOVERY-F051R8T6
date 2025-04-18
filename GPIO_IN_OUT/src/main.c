#include "rcc.h"
#include "gpio.h"

int main()
{
	rcc_clock_config();
	gpio_set();
	int a = 80000;
	while(1)
	{
		int BTN_PRESSED = 0;
		while(!BTN_PRESSED)
		{
			BTN_PRESSED = (GPIOA->IDR & (1<<0));
		}
		for(int i=0;i<a;i++);	// Simple wait condition for Debouncing effect of SW
		GPIOC->ODR^= (1<<8);
	}
	return 0;
}
