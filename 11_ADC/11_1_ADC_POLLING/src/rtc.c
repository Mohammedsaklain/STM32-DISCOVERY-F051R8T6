#include "custom.h"
#include "rtc.h"

RTC_Set_Time_STRUCT Set_Time;
RTC_Get_Time_STRUCT Get_Time;
RTC_Get_Date_STRUCT Get_Date;

void RTC_Init(void){

    /* Unlock all the RTC write protectd registers following to the below key pattern in RCC->WPR Register*/
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    /* INIT mode used to program time, date register (RTC_TR and RTC_DR), and 
    prescaler register (RTC_PRER). Counters are stopped and start counting from the new 
    value when INIT is reset.*/
    RTC->ISR |= RTC_ISR_INIT;
    #ifndef HOST_UNIT_TEST
        while(!((RTC->ISR) & (RTC_ISR_INITF)));   /* Wait for INITF flag is set*/
    #endif
    /* To get the 1Hz clock, set the prescalar based on calculations*/
    RTC->PRER &= ~(0xFFFFFF);
    RTC->PRER |= (0x7C<<16);    // PREDIV_A  - 124 (0x7F<<16); - for 32.768KHz
    RTC->PRER |= (0x13F<<0);    // PREDIV_S  - 319 (0xFF<<0); - for 32.768KHz
}

void RTC_Set_Time(char AM_PM,uint8_t Hour, uint8_t Minute, uint8_t Seconds){
    RTC->TR &= ~(0x7F7F7F);             //Clear all the time register bits 
    if(AM_PM == 'A'){
        RTC->TR &= ~RTC_TR_PM;          // Set for AM
    }
    else{
        RTC->TR |= RTC_TR_PM;           // Set for PM
    }
    Set_Time.Hr_Tens = Hour/10;         // Hour Tens position
    Set_Time.Hr_Unit = Hour%10;         // Hour Unit position
    Set_Time.Mn_Tens = Minute/10;
    Set_Time.Mn_Unit = Minute%10;
    Set_Time.Sc_Tens = Seconds/10;
    Set_Time.Sc_Unit = Seconds%10;
    RTC->TR |=  ((Set_Time.Hr_Tens<<20) |  (Set_Time.Hr_Unit<<16) | (Set_Time.Mn_Tens<<12) | \
                (Set_Time.Mn_Unit<<8) | (Set_Time.Sc_Tens<<4) | (Set_Time.Sc_Unit<<0));
}

void RTC_Set_Date(uint8_t Date, uint8_t Day, uint8_t Month, uint16_t Year){
    uint16_t YR = Year - 2000; // Set the last 2 digits of the year, ex 2025 -> 25 
    RTC->DR |= (((YR/10)<<20) | ((YR%10)<<16) | (Day<<13) | ((Month/10)<<12) | ((Month%10)<<8) | ((Date/10)<<4) | ((Date%10)<<0));
}

void RTC_Start(void){
    RTC_Init();
	RTC_Set_Time('A',7,0,0);        // Start with default time 7:00 AM
	RTC_Set_Date(1,MONDAY,1,2002);  // Start with default Date Monday/1/1/2002
    
    RTC->CR &= ~(RTC_CR_FMT);       // Set to Hour Format to AM/PM
    RTC->CR |= RTC_CR_TSE;          // Time stamp enable
    RTC->ISR &= ~(RTC_ISR_INIT);    // Exit from Initialization mode, now free running mode
    RTC->WPR = 0xFF;                // This should not only to be 0xFF, since writing wrong key reactivates the write protection
    PWR->CR &= ~PWR_CR_DBP;         // Disable access to RTC register
}

void RTC_Get_Time(void){
    uint32_t current_time   = RTC->TR;
    Get_Time.hours          = ((((current_time & 0x300000)>>20)*10) + ((current_time & 0xF0000)>>16));  // Get hour tens & unit time & combine them to get in Hr
    Get_Time.minutes        = ((((current_time & 0x7000)>>12)*10) + ((current_time & 0xF00)>>8));   // Get minute tens & unit time & combine them to get in Mn
    Get_Time.seconds        = ((((current_time & 0x70)>>4)*10) + ((current_time & 0xF)>>0));   // Get sec tens & unit time & combine them to get in Sc
    Get_Time.am_pm          = ((current_time & 0x400000)>>22);  // AM -0 or PM - 1
}

void RTC_Get_Date(void){
    uint32_t current_date   = RTC->DR;
    Get_Date.day            = ((current_date & 0xE000)>>13);    //Day
    Get_Date.date           = ((((current_date & 0x30)>>4)*10) + ((current_date & 0xF)>>0)); //Date
    Get_Date.month          = ((((current_date & 0x1000)>>12)*10) + ((current_date & 0xF00)>>8)); //Month
    Get_Date.year           = ((((current_date & 0xF00000)>>20)+2000) + ((current_date & 0xF0000)>>16)); //year
}