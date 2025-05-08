#include "main.h"

int main()
{
	Digital_Out(GPIOC,8);
	GPIOC->ODR |= (1<<8);

	//Selecting PA2(TX) & PA3(RX) as alternate function
	GPIOA->MODER &= ~((3<<4) | (3<<6));     // Clear bits
    GPIOA->MODER |= (2<<4) | (2<<6);        // Selecting PA2(TX) & PA3(RX) as alternate function
    GPIOA->AFR[0] &= ~((1<<8) | (1<<12));   // Clear Bits
    GPIOA->AFR[0] |= (1<<8) | (1<<12); 

	// Alternate function for TIM3- CH2
	Gpio_Init(GPIOA,7,AF,NO_PUPD);	
	Gpio_Af(GPIOA,7,AF1);

	Init_UART();

	Timer_Init(T3,7999,65535,FALSE);
	Timer_Default_Start(T2,FALSE);
	Timer_Input_Capture(T3);

	//int i=0;
	while(1)
	{
		transmit_Integer(RF_DATA_READ(Timer_Read_Input_Capture(T3)));
		//transmit_Integer(i);
		//Delay_mS(T2,1000);
		//i++;
	}
	return 0;
}
