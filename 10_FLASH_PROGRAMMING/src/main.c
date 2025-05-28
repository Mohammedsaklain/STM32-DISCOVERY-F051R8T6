#include "main.h"

#ifndef HOST_UNIT_TEST
	int main(){
		UART_Init();
		Flash_Storage_Init();
		uint8_t Data_Log[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
		enum FLASH_COMMAND_STATUS status;
		
		uint16_t Data2[] = {0x0010, 0x0020};
		status = Flash_Store_Data(Data_Log, sizeof(Data_Log));
		status = Flash_Store_Data((uint8_t*)&Data2,sizeof(Data2));
		if(status == FLASH_OK){
			MS_printf("Data Logged Successfull\r\n");
		}else{
			MS_printf("Failed to Log Data %d\r\n",status);
		}
		
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