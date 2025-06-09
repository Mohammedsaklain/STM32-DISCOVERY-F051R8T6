#include "custom.h"
#include "ext_int.h"
#include "gpio_dr.h"
#include "uart.h"

#ifndef HOST_UNIT_TEST
	int main(){
		GPIOC->MODER &= ~((3U<<18) | (3U<<16));
		GPIOC->MODER |=  ((1U<<18) | (1U<<16));
		__enable_irq();
		External_INT_Init();
		while(1)
		{
		}
		return 0;
	}	
#else	/* In origin, There should not be any infinite loops present*/
	int origin(){
		return 0;
	}
#endif



	


/* provide _exit implementation, this function is called by exit() and
it typically means the program has finished or encountered a critical error.*/
void _exit(int status) {
    // In a bare-metal system, there's no OS to return to.
    // Common actions are:
    // Loop indefinitely (halts program execution)
    while(1);

    /* Future update to add WDG or System reset by removing infinite while loop*/
}