#ifndef GPIO_DR_H_
#define GPIO_DR_H_

#define HIGH 1
#define LOW  0

enum gpio_mode
{IN,OUT,AF,ANALOG};

enum gpio_pullup_down
{NO_PUPD,PUP,PDOWN};

enum gpio_af
{AF0,AF1,AF2,AF3,AF4,AF5,AF6,AF7};

void Gpio_Init(GPIO_TypeDef *PORT, uint8_t pin, uint8_t MODE, uint8_t PUPD);
void Gpio_Af(GPIO_TypeDef *PORT, uint8_t pin, uint8_t AF_NO);
void Digital_Out(GPIO_TypeDef *PORT, uint8_t pin);
void Gpio_Write(GPIO_TypeDef *PORT, uint8_t pin, uint8_t level);
uint8_t Gpio_Read(GPIO_TypeDef *PORT, uint8_t pin);
#endif