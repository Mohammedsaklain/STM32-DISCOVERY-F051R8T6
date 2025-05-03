#include "rcc.h"
#include "gpio.h"
#include "timer_dr.h"

int main()
{
	Digital_Out(GPIOC,8);
	Digital_Out(GPIOC,9);
	Timer_Start(T1, TRUE);

	while(1)
	{
		Gpio_Write(GPIOC,9,1);
		for(int i=0;i<80000;i++);
		Gpio_Write(GPIOC,9,0);
		for(int i=0;i<80000;i++);
	}
	return 0;
}
