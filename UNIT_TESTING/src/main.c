#include "main.h"

int main(void)
{
	Gpio_Init(GPIOC,8,OUT,PUSH_PULL,NO_PUPD);
	Gpio_Init(GPIOC,9,OUT,PUSH_PULL,NO_PUPD);

	while(1)
	{
		Gpio_Write(GPIOC,8,HIGH);
		Gpio_Write(GPIOC,9,HIGH);
	}
	return 0;
}
