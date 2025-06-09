#include "rcc.h"
#include "gpio.h"
#include "ext_int.h"

int main()
{
	GPIOC->MODER &= ~((3U<<16) | (3U<<18));
	GPIOC->MODER |= ((1<<8) | (1<<9));
	External_INT_Init();
	while(1)
	{
	}
	return 0;
}
