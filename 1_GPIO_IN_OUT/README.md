# GPIO in STM32F0 

Each port(GPIO) is a 32-bit wide that allows you to control up to 16 I/O pins per port. 

### Essential GPIO registers:

1. Each GPIO has four 32-bit configuration registers: Used for Mode(IN/OUT/Analog/Alternate), Output type(Open drain/Push Pull), Pin speed(Low, medium or fast), pin pull up, pull down, or float. 
```
    GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR, GPIOx_PUPDR
```
a. GPIOx_MODER Configuration: 
* 00: Input Mode(reset value)
* 01: General purpose output Mode
* 10: Alternate function
* 11: Analog mode

b. GPIOx_OTYPER Configuration: 
* 0: Output Push-Pull(reset value)
* 1: Output Open-drain

c. GPIOx_OSPEEDR Configuration:
* x0: Low Speed
* 01: Medium Speed
* 11: High Speed

d. GPIOx_PUPDR Configuration: 
* 00: NO-Pull-up/Down
* 01: Pull-Up
* 10: Pull-Down

2. Two 32-bit data registers: To read input data(IDR) from a pin or to write to a pin(ODR)
```
    GPIOx_IDR, GPIOx_ODR
```
3. One 32-bit set/reset register: Used for setting and clearing bits. 
```
    GPIOx_BSRR
```
GPIOx_BSRR Configuration:
* Bits [15:0] are for setting (writing 1 sets the corresponding ODR bit).
* Bits [31:16] are for resetting (writing 1 resets the corresponding ODR bit)

4. Only Port-A & Port-B has 32-bit locking and alternate function registers: To lock the configuration of port bits(LCKR), or Pins can be multiplexed to serve as peripherals (UART, SPI, I2C, Timers, etc.) instead of general-purpose I/Os
```
    GPIOx_LCKR, GPIOx_AFRL, GPIOx_AFRH
```
GPIOx_AFRL/H Configuration: 
* Selects the alternate function (AF0 to AF7) for each pin when configured in alternate function mode. AFRL is for pins 0-7, AFRH is for pins 8-15. Each pin uses 4 bits