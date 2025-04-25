#include "rcc.h"
#include "gpio.h"
#include "uart.h"

/* Still Need to develop */

int main()
{
	gpio_set();
	Init_UART();

	while(1)
	{
		MSprint("Hello Kaynes unit - %d",0);
		for(int i=0;i<9000000;i++);
	}
	return 0;
}
