#include "main.h"

#ifndef HOST_UNIT_TEST
	int main(){
		RTC_Start();
		while(1)
		{
			RTC_Get_Time();
		}
		return 0;
	}	
#else	/* In origing, There should not be any infinite loops present*/
	int origin(){
		RTC_Start();
		return 0;
	}
#endif
