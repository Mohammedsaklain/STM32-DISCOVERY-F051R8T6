#include "rcc.h"
#include "gpio_dr.h"
#include "stm32f0xx.h"
#include "timer_dr.h"


uint32_t LAST_COUNT = 0;
uint32_t CURRENT_COUNT = 0;
uint32_t TIME_INTERVAL = 0;

int main()
{
	Digital_Out(GPIOC,8);
	GPIOC->ODR |= (1<<8);

	Gpio_Init(GPIOA,5,AF,NO_PUPD);	// Alternate function for TIM2 - CH1
	Gpio_Af(GPIOA,5,AF2);

	Gpio_Init(GPIOA,7,AF,NO_PUPD);	// Alternate function for TIM3- CH2
	Gpio_Af(GPIOA,7,AF1);

	/* Here TIM2 is used as PWM generation of period 2sec which will be given as INPUT capture for TIM3 - CH2*/
	Timer_Init(T2,0,799,FALSE);		//for 100u sec
	Timer_PWM_Init(T2,CH1,50);  

	Timer_Init(T3,0,63999,FALSE);	//8m
	Timer_Input_Capture(T3);

	while(1)
	{
		while(!(TIM3->SR & TIM_SR_CC2IF));	// wait till rising edge pulse is present
		TIM3->SR &= ~(1<<0);
		CURRENT_COUNT = TIM3->CCR2;
		TIME_INTERVAL = CURRENT_COUNT - LAST_COUNT;
		LAST_COUNT = CURRENT_COUNT;

	}
	return 0;
}
