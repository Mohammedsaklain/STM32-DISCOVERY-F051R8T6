#include "custom.h"
#include "gpio_dr.h"
#include "uart.h"
#include "crc.h"

#ifndef HOST_UNIT_TEST

int main(){
    uint32_t DATA = 0xDEADBEEF, Result;
    UART_Init();
    CRC_Init();
	while(1){
        Result = CRC_Calculate_32B(DATA);
        for(int i=0;i<60000;i++);
        for(int i=0;i<60000;i++);
        MS_printf("Input Data = %X\r\n", DATA);
        MS_printf("Calculated CRC = %X\r\n",Result);
        for(int i=0;i<60000;i++);
        for(int i=0;i<60000;i++);
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
    status = status;
    while(1);
    /* Future update to add WDG or System reset by removing infinite while loop*/
}