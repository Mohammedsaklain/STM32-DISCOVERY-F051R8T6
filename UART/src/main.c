#include "rcc.h"
#include "gpio.h"

int main()
{
	rcc_clock_config();
	gpio_set();
	long a = 200000;
	while(1)
	{
		GPIOC->ODR &= ~(3<<8);
		for(long i=0; i<a; i++);
		GPIOC->ODR |= 3<<8;
		for(long i=0; i<a; i++);
	}
	return 0;
}
