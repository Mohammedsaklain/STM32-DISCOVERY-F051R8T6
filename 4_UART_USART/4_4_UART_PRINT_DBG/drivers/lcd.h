#ifndef LCD_H_
#define LCD_H_

#include "main.h"

#define LEFT  0x18
#define RIGHT 0x1C

#define DISPLAY_WIDTH 16

void Lcd_Gpio_Init(void);
void Lcd_Init(void);
void Lcd_Delay(void);
void Lcd_RS_Command(unsigned char cmd);
void Lcd_Write_Data(char *Data);
void Lcd_Scroll_Data(char *Data, uint8_t Scrol_Left_Right);
void Lcd_Set_CurSsor(uint8_t row, uint8_t col);
#endif
