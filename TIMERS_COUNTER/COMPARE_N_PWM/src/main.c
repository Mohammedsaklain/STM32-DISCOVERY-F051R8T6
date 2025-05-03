#include "rcc.h"
#include "gpio_dr.h"
#include "timer_dr.h"

int main()
{
	Gpio_Init(GPIOA,2,AF,NO);
	Gpio_Af(GPIOA,2,AF0);
	Timer_Start(T15, FALSE);
	Timer_Compare(T15, CH1);

	while(1)
	{

	}
	return 0;
}
