#include "main.h"

uint32_t RF_DATA=0;
uint8_t RF_DATA_CNT=0;
uint8_t RF_DATA_SET_FLAG=FALSE;

uint32_t RF_DATA_READ(uint32_t time_interval)
{
	uint32_t temp=0;
	if(RF_DATA_CNT!=25)
	{
		if((time_interval<=350)&&(time_interval>=250))
		{
			RF_DATA&=~(1<<RF_DATA_CNT);
			RF_DATA_CNT++;
		}
		else if((time_interval<=750)&&(time_interval>=650))
		{	
			RF_DATA|=(1<<RF_DATA_CNT);
			RF_DATA_CNT++;
		}
        return RF_DATA_SET_FLAG;
	}
	else
	{
		temp = RF_DATA;
		RF_DATA = 0;
		RF_DATA_CNT = 0;
        RF_DATA_SET_FLAG=TRUE;
		return temp;
	}
}
