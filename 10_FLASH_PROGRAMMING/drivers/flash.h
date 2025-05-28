#ifndef FLASH_H_
#define FLASH_H_

#include "main.h"

/* symbols from linker*/
extern unsigned long __flash_user_data_start__;
extern unsigned long __flash_user_data_end__;

/* User Storage area, total of 4KB size*/
#define FLASH_PAGE_SIZE             (1024U)
#define FLASH_USER_DATA_START_ADDR  ((uint32_t)&__flash_user_data_start__)
#define FLASH_USER_DATA_END_ADDR    ((uint32_t)&__flash_user_data_end__)
#define FLASH_USER_DATA_SIZE        (FLASH_USER_DATA_END_ADDR - FLASH_USER_DATA_START_ADDR)
#define FLASH_USER_DATA_NUM_PAGES   (FLASH_USER_DATA_SIZE / FLASH_PAGE_SIZE)


enum FLASH_COMMAND_STATUS{
    FLASH_OK        =0,
    FLASH_ERROR     =1,
    FLASH_BUSY      =2,
    FLASH_LOCKED    =3,
    FLASH_UNLOCKED  =4,
    FLASH_TIMEOUT   =5,
};

uint8_t Flash_Status(void);
uint8_t Flash_Memory_Unlock(void);
uint8_t Flash_Memory_Lock(void);
uint8_t Flash_Memory_Erase_Pages(uint32_t start_page_addr,uint32_t num_pages);
uint8_t Flash_Program_Halfword(uint32_t Address, uint16_t Data);
uint8_t Flash_Read_Byte(uint32_t Address);
uint16_t Flash_Read_Halfword(uint32_t Address);
uint32_t Flash_Read_Word(uint32_t Address);

uint32_t Flash_Get_Current_Write_Addr(void);
uint8_t Flash_Store_Data(const uint8_t *Data, uint32_t size);
void Flash_Storage_Init(void);
#endif