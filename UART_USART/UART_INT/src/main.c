#include "rcc.h"
#include "gpio.h"
#include "uart.h"

int main()
{
	rcc_clock_config();
	gpio_set();
	Init_UART();

	while(1)
	{
	}
	return 0;
}
