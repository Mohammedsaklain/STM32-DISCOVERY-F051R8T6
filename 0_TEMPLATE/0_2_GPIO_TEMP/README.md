## System Tick Timer

The SysTick is a 24-bit down counter driven by the system clock. It counts down from an initial value to 0. When it reaches 0, in the next clock, it underflows and it raises a flag called COUNTFLAG and reloads the initial value and starts all over. We can set the initial value to a value between 0x000000 to 0xFFFFFF

System Timer registers:

1. SysTick Control & Status Register (STK_CSR) <br>
2. SysTick reload value register (STK_RVR) <br>
3. SysTick current value register (STK_CVR) <br>