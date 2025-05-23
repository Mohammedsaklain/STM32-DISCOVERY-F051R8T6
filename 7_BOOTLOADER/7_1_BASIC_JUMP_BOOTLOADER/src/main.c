#include "main.h"
//#include "core_cm3.h"
#include "boot.h"

int main()
{
	GPIOC->MODER &= ~(3<<18); /*PC9 - LED for app code*/
	GPIOC->MODER |=  (1<<18);
	while(1)
	{
		GPIOC->ODR ^= (1<<9);
		for(int i=0;i<800000;i++){}
	}
	return 0;
}
