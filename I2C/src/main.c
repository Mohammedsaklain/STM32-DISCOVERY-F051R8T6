#include "rcc.h"
#include "gpio.h"
#include "ext_int.h"

int main()
{
	gpio_set();
	Init_Ext_Int();
	int a = 80000;
	while(1)
	{
		GPIOC->ODR ^= (1<<9);
		for(int i=0;i<a;i++);
	}
	return 0;
}
