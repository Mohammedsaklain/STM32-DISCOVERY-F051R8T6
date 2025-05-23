/*  file        :   lcd.c / lcd.h
    Created time:   15/05/25 - 15:06
    Author      :   Mohammed Saklain*/

#include "main.h"

void Lcd_Gpio_Init(void)
{
    /* GPIOA as D0-D7*/
    Gpio_Init(GPIOA,0,OUT,PUSH_PULL,NO_PUPD);   /*PA0*/
    Gpio_Init(GPIOA,1,OUT,PUSH_PULL,NO_PUPD);   /*PA1*/
    Gpio_Init(GPIOA,2,OUT,PUSH_PULL,NO_PUPD);   /*PA2*/
    Gpio_Init(GPIOA,3,OUT,PUSH_PULL,NO_PUPD);   /*PA3*/
    Gpio_Init(GPIOA,4,OUT,PUSH_PULL,NO_PUPD);   /*PA4*/
    Gpio_Init(GPIOA,5,OUT,PUSH_PULL,NO_PUPD);   /*PA5*/
    Gpio_Init(GPIOA,6,OUT,PUSH_PULL,NO_PUPD);   /*PA6*/
    Gpio_Init(GPIOA,7,OUT,PUSH_PULL,NO_PUPD);   /*PA7*/

    /* PB0 - RS*/
    Gpio_Init(GPIOB,0,OUT,PUSH_PULL,NO_PUPD);
    /* PB1 - Enable*/
    Gpio_Init(GPIOB,1,OUT,PUSH_PULL,NO_PUPD);
    /* R/W pin of LCD is connected to GND(0) for Write Operation*/
}

void Lcd_Init(void)
{
    Lcd_Gpio_Init();
    Lcd_Delay();
    Lcd_RS_Command(0x38);       /* Operate in 8 Bit mode*/
    Lcd_RS_Command(0x01);       /* Clear Screen*/
    Lcd_RS_Command(0x0C);       /* Display On, NO Cursor Blinking*/
}

/* Small Delay function for LCD*/
void Lcd_Delay(void)
{
    for(int i=0;i<3000;i++);
}

/* Register Select Commands*/
void Lcd_RS_Command(unsigned char cmd)
{
    Gpio_Write(GPIOB,0,LOW);    /* Clear RS - select Command Register*/
    GPIOA->ODR &= ~(0xFF);      /* Clear Output*/
    GPIOA->ODR |= cmd;          /* command on GPIOA (sending through D0-D7)*/
    
    /* We need to make High and low pulse at EN to make changes*/
    GPIOB->ODR|= (1<<1);
    Lcd_Delay();
    GPIOB->ODR&= ~(1<<1);

    Gpio_Write(GPIOB,0,HIGH);    /* Return back to Data Register*/
}

void Lcd_Write_Data(char *Data)
{
    Gpio_Write(GPIOB,0,HIGH);    /* Set RS - select Data Register*/
    uint8_t Cnt=1;
    for(uint16_t i=0;Data[i]!='\0';i++)
    {
        /* make sure that String length doesn't exceed 16( which is a limit in 1 Row)*/
        if(Cnt>16)
        {
            Lcd_RS_Command(0xC0);       /* Force Cursor to second line beginning*/
            Cnt = 1;                    /* To limit only 1 time execution of this loop*/
        }
        GPIOA->ODR &= ~(0xFF);          /* Clear Output*/
        GPIOA->ODR |= Data[i];          /* Data on GPIOA (sending through D0-D7)*/
        
        GPIOB->ODR|= (1<<1);
        Lcd_Delay();
        GPIOB->ODR&= ~(1<<1);
        Cnt++;
    }
}

void Lcd_Set_Cursor(uint8_t row, uint8_t col)
{
    uint8_t addr;
    if(row==0){
        addr = 0x00 + col;  // DDRAM address for row 0 starts at 0x00
    }else{
        addr = 0x40 + col;  // DDRAM address for row 1 starts at 0x40
    }
    Lcd_RS_Command(0x80 | addr);    //DB7 is 1, so 0x80
}


void Lcd_Scroll_Data(char *Data, uint8_t Scrol_Left_Right)
{
    /* To calculate the Data Length*/
    uint16_t Data_Len =0,Scr_Cnt =0;
    while(Data[Data_Len]!='\0'){
        Data_Len++;
    }
    Lcd_RS_Command(0x01);       /* clear Display*/
    Lcd_Delay();

    if(Data_Len<=DISPLAY_WIDTH){
        if(Scrol_Left_Right==RIGHT){
            Lcd_Set_Cursor(0,0);
            Lcd_Write_Data(Data);
            Scr_Cnt=16;
        }else{
            Lcd_Set_Cursor(0,15);
            Lcd_Write_Data(Data);
            Scr_Cnt = Data_Len + 16;
        }
        
    }
    Lcd_Delay();

    for(int j=0;j<Scr_Cnt;j++)
    {
        Lcd_RS_Command(Scrol_Left_Right);
        for(int i=0;i<200000;i++);
    }
}