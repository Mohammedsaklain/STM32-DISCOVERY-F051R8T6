#include "rcc.h"
#include "gpio.h"
#include "systick.h"

int main()
{
	gpio_set();
	Init_SysTick();

	while(1)
	{
	}
	return 0;
}
