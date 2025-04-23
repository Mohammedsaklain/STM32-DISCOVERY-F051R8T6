#include "rcc.h"
#include "gpio.h"
#include "timer.h"

void Delay1Sec(void);

int main()
{
	rcc_clock_config();
	gpio_set();
	Timer2_Init();
	while(1)
	{
		GPIOC->ODR^= (1<<8);
		Delay1Sec();
	}
	return 0;
}

void Delay1Sec(void)
{
	/*HOLDS THE TOTAL COUNT FROM TM2_CNT REGISTER TO RECORD HOW MUCH TIME ELAPSED.*/
	unsigned int counter = 0;
	//HOLDS THE COUNT FOR THE COUNTER TO COUNT TO.
	unsigned int goalCount = 8000000;
	//HOLDS THE MOST RECENT VALUE OBTAINED FROM TIM2_CNT.
	unsigned int currentCntVal = 0;
	//HOLDS THE PREVIOUS VALUE OBTAINED FROM TIM2_CNT.
	unsigned int prevCntVal = 0;
	//HOLDS RESULT OF CALCULATION BETWEEN CURRENT AND PREVIOUS COUNTS.
	unsigned int countToAdd = 0;
		
	//GET INITIAL VALUE OF CNT
	prevCntVal = TIM2->CNT; 
		
	//LOOP UNTIL COUNTER IS EQUAL OR EXCEED GOAL COUNT
	while(counter < goalCount)
	{
		//GET NEWEST COUNT
		currentCntVal = TIM2->CNT;
			
		//HANDLE SITUATION WHERE TIM2_CNT RESET
		if(currentCntVal < prevCntVal)
		{
			//GET THE COUNT BEFORE THE CNT REGISTER RESET AND THEN 
			//ADD THE COUNT AFTER IT RESET TO GET ELAPSED COUNT
			countToAdd = (8000000 - prevCntVal) + currentCntVal;
		}
		else
		{
			//SSUBTRACT CURRENT COUNT FROM PREVIOUS COUNT TO GET ELAPSED COUNT
			countToAdd = currentCntVal - prevCntVal;
		}
			
		//ADD ELAPSED COUNT TO THE COUNTER
		counter += countToAdd;
			
		//CURRENT COUNT NOW BECOMES PREVIOUS COUNT
		prevCntVal = currentCntVal;
	}
}
