The 3 main sources of Clock for the RTC, which will be prescaled down to 1Hz
1. LSE      - Low Speed External<br>
2. HSE      - High Speed External<br>
3. LSI RC   - Low Speed Internal - 40 KHz for RTC & IWDG<br>

### Steps to setup RTC: 
1. In reset state, the RTC and backup registers are protected against parasitic write access. DBP bit must be set in order to enable RTC registers write access.
``` C
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;      // Power Clock Enable
    PWR->CR       = PWR_CR_DBP;        // Disable RTC domain Write protection
    RCC->BDCR    |= RCC_BDCR_RTCSEL_1; // LSI-40 KHz clk for RTC
    RCC->BDCR    |= RCC_BDCR_RTCEN;    // Enable RTC clk
```
2. After RTC domain reset, all the RTC registers are write-protected. Writing to the RTC registers is enabled by writing a key into the Write Protection register, RTC_WPR. The following steps are required to unlock the write protection on all the RTC registers except for RTC_TAFCR, RTC_BKPxR and RTC_ISR[13:8].
``` C
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
```
Writing a wrong key reactivates the write protection. The protection mechanism is not affected by system reset.
3. Enable the Initialization mode. INIT mode used to program time, date register (RTC_TR and RTC_DR), and prescaler register (RTC_PRER). Counters are stopped and start counting from the new value when INIT is reset
``` C
    RTC->ISR |= RTC_ISR_INIT;
    while(!(RTC->ISR) & (RTC_ISR_INITF));   /* Wait for INITF flag is set*/
```
4. Set the Prescaler register configuration based on our RTC clock input.
* RTC input clock =  40000 Hz<br>
* In RTC_PRER register: ->A 7-bit(22-16) asynchronous prescaler configured through the PREDIV_A bits of the 
RTC_PRER register.
->A 15-bit(14-0) synchronous prescaler configured through the PREDIV_S bits of the 
RTC_PRER register.
-> The multiplication of both should be equal to 1Hz clock to the RTC module.
* In our case for RTC clock of 40KHz -> 1Hz<br>
1Hz = (RTC_Clk)/((PREDIV_S+1)*(PREDIV_A+1))
So, PREDIV_S = 313(0x139) and PREDIV_A = 126(0x7F)
``` C
    RTC->PRER &= ~(0xFFFF);
    RTC->PRER |= (0x7C<<16);    // PREDIV_A  - 124
    RTC->PRER |= (0x13F<<0);    // PREDIV_S  - 319
```
4. Then follow below steps and exit from initialization mode, now free running mode
``` C
    RTC->CR &= ~(RTC_CR_FMT);       // Set to Hour Format to AM/PM
    RTC->CR |= RTC_CR_TSE;          // Time stamp enable
    RTC->ISR &= ~(RTC_ISR_INIT);    // Exit from Initialization mode, now free running mode
    RTC->WPR = 0xFF;                // This should not only to be 0xFF, since writing wrong key reactivates the write protection
    PWR->CR &= ~PWR_CR_DBP;         // Disable access to RTC register
```