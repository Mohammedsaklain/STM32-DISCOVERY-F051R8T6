#ifndef RTC_H_
#define RTC_H_
#include "main.h"

enum Week_Days
{MONDAY=1,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY,SATURDAY,SUNDAY};

typedef struct RTC_Set_Time_STRUCT{
    uint8_t Hr_Tens;
    uint8_t Hr_Unit;
    uint8_t Mn_Tens;
    uint8_t Mn_Unit; 
    uint8_t Sc_Tens; 
    uint8_t Sc_Unit;
}RTC_Set_Time_STRUCT;

typedef struct RTC_Get_Time_STRUCT{
    uint32_t am_pm;
    uint32_t hours;
    uint32_t minutes;
    uint32_t seconds;
}RTC_Get_Time_STRUCT;

typedef struct RTC_Get_Date_STRUCT{
    uint32_t day;
    uint32_t date;
    uint32_t month;
    uint32_t year;
}RTC_Get_Date_STRUCT;


void RTC_Init(void);
void RTC_Set_Time(char AM_PM,uint8_t Hour, uint8_t Minute, uint8_t Seconds);
void RTC_Set_Date(uint8_t Date, uint8_t Day, uint8_t Month, uint16_t Year);
void RTC_Start(void);
void RTC_Get_Time(void);
void RTC_Get_Date(void);

#endif