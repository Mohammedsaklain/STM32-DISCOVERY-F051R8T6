#include "custom.h"
#include "flash.h"

static uint32_t next_flash_write_addr;
//static uint32_t boot_flash_next_write_addr;

/* Function to check proper functioning & Clear necessary flags*/
uint8_t Flash_Status(void){
    uint32_t timeout=0;
    /* Check that no main flash memory operation is ongoing. Busy Flag*/
    while(((FLASH->SR) & (FLASH_SR_BSY))){
        /* A small delay function for changes to takes place*/
        timeout++;
        if(timeout>1000){
            return FLASH_TIMEOUT;   // It means that BSY flag didn't reset, Timeout error occured
        }
    }
    /* If programming or Write protection error has occured?*/
    if((FLASH->SR & (FLASH_SR_PGERR | FLASH_SR_WRPERR))!=0){
        FLASH->SR |= (FLASH_SR_PGERR | FLASH_SR_WRPERR);    // Clear all error flags
        return FLASH_ERROR;
    }
    /* Check that Flash Erase/Programming is completed? */
    if((FLASH->SR & FLASH_SR_EOP)!=0){
        FLASH->SR = FLASH_SR_EOP;
        return FLASH_OK;
    }
    // If BSY is not set, no errors, and EOP is not set, it means no operation just completed,
    // but the Flash is ready for a new operation. Return OK to indicate ready.
    return FLASH_OK;
}

uint8_t Flash_Memory_Unlock(void){
    uint8_t status = Flash_Status();
    if(status==FLASH_TIMEOUT || status == FLASH_ERROR){
        return status;
    }

    if((FLASH->CR & FLASH_CR_LOCK)!=0){         /* Write to 1 only. When it is set, it indicates that the flash is locked*/
        /* Flash Key Register: Unlock keys*/
        FLASH->KEYR = 0x45670123;
        FLASH->KEYR = 0xCDEF89AB;
    }
    status = Flash_Status();
    if(status!=FLASH_OK){
        return status;
    }

    /* Check wether Unlock sequence succeded? */
    if((FLASH->CR & FLASH_CR_LOCK)==0){
        return FLASH_UNLOCKED;
    }else{
        return FLASH_LOCKED;    /* Still locked means, lock sequence failed*/
    }
}

uint8_t Flash_Memory_Lock(void){
    FLASH->CR |= FLASH_CR_LOCK;     // Set the Lock bit
    uint8_t status = Flash_Status();
    if (status == FLASH_TIMEOUT || status == FLASH_ERROR){
        return status;
    }
    /* Check wether lock sequence succeded? */
    if((FLASH->CR & FLASH_CR_LOCK)!=0){
        return FLASH_LOCKED;
    }else{
        return FLASH_ERROR;    /* Still unlocked means, Indicates error */
    }
}


uint8_t Flash_Memory_Erase_Pages(uint32_t start_page_addr,uint32_t num_pages){    
    uint32_t current_page_addr  = start_page_addr;
    uint8_t status;

    status = Flash_Memory_Unlock();             /* Ensure Memory is unlocked */
    if(status!=FLASH_UNLOCKED){
        return status;
    }

    for(uint8_t i=0;i<num_pages;i++){
        status = Flash_Status();            // Wait for flash to get settled
        if(status!=FLASH_OK){
            Flash_Memory_Lock();            // Lock memory again
            return status;
        }
        // Clear any pending error flags and EOP before starting a new operation
        FLASH->SR = FLASH_SR_EOP | FLASH_SR_PGERR | FLASH_SR_WRPERR;

        FLASH->CR |= FLASH_CR_PER;          // Set Page Erase command
        FLASH->AR = current_page_addr;      // Write the address of the page to be erased
        FLASH->CR |= FLASH_CR_STRT;         // Start erase operation

        status = Flash_Status();            // wait for erase to complete
        if(status!=FLASH_OK){
            FLASH->CR &= ~FLASH_CR_PER;      /* Clear to Page erase command*/
            Flash_Memory_Lock();
            return status;
        }
        FLASH->CR &= ~FLASH_CR_PER;             // Clear PER bit after each page erase
        current_page_addr += FLASH_PAGE_SIZE;   // Move to next page
    }
    Flash_Memory_Lock();    // Lock after all pages erased
    return FLASH_OK;
}

uint8_t Flash_Program_Halfword(uint32_t Address, uint16_t Data){
    uint8_t status;
    // Address must be half-word aligned (divisible by 2)
    if ((Address % 2) != 0) {
        return FLASH_ERROR;
    }

    status = Flash_Memory_Unlock();
    if(status!=FLASH_UNLOCKED){
        return status;
    }

    status = Flash_Status();
    if(status != FLASH_OK) {
        Flash_Memory_Lock();
        return status;
    }
    // Clear any pending error flags and EOP before starting
    FLASH->SR = FLASH_SR_EOP | FLASH_SR_PGERR | FLASH_SR_WRPERR;
    FLASH->CR |= FLASH_CR_PG; // Set Program Enable bit
    *(volatile uint16_t *)Address = Data;       // Write Data to target address

    status = Flash_Status(); // Wait for program to complete
    if (status != FLASH_OK) {
        // If an error occurred during programming, clear PG bit and return error
        FLASH->CR &= ~FLASH_CR_PG;
        Flash_Memory_Lock();
        return status;
    }

    FLASH->CR &= ~FLASH_CR_PG;          // Clear Program Enable bit
    Flash_Memory_Lock();                       // Lock Flash after operation

    return status;
}

uint8_t Flash_Read_Byte(uint32_t Address){
    return *(volatile uint8_t *)Address;
}

uint16_t Flash_Read_Halfword(uint32_t address) {
    // Address must be half-word aligned (divisible by 2) for direct read
    if ((address % 2) != 0) {
        // Handle unaligned access - read byte by byte or return error
        return address;
    }
    return *(volatile uint16_t *)address;
}

uint32_t Flash_Read_Word(uint32_t address) {
    // Address must be word aligned (divisible by 4) for direct read
    if ((address % 4) != 0) {
        // Handle unaligned access - read half-word by half-word or return error
        return address;
    }
    return *(volatile uint32_t *)address;
}

/* Local function to find the empty region*/
static uint32_t find_first_free_flash_addr(void){
    uint32_t addr = FLASH_USER_DATA_START_ADDR;
    /* Check through user data region of half words emptyness*/
    while(addr<FLASH_USER_DATA_END_ADDR){
        if(*(volatile uint16_t *)addr != 0xFFFF){
            /* If yes, means this address space have been written*/
            addr+=sizeof(uint16_t);
        }else{
            /* If found empty half word with 0xFFFF*/
            return addr;
        }
    }
    /* If enters here, means entire region is written, send full region to erase*/
    return FLASH_USER_DATA_START_ADDR;
}

/* Main function for starting with auto data save in without specifying location address*/
void Flash_Storage_Init(void){
    next_flash_write_addr = find_first_free_flash_addr();
    if((next_flash_write_addr == FLASH_USER_DATA_START_ADDR)&&(*(volatile uint16_t *)FLASH_USER_DATA_START_ADDR != 0xFFFF)){
        /* means all the region is full, erase all the pages and start with fresh*/
        Flash_Memory_Erase_Pages(FLASH_USER_DATA_START_ADDR, FLASH_USER_DATA_NUM_PAGES);
    }
}

uint8_t Flash_Store_Data(const uint8_t *Data, uint32_t size){
    uint8_t status;
    uint32_t current_addr = next_flash_write_addr;

    /* Ensure size is not-zero*/
    if(size==0){
        return FLASH_ERROR;
    }

    /* Calculate the required Half-words & bytes required*/
    /* ex. size = 1(byte)  halfwords = 1(16bits), bytes = 2(16bits)*/
    /* ex. size = 2(bytes) halfwords = 1(1.5~1, 16bits),bytes = 2(16)*/
    uint32_t required_halfwords = (size + 1) / 2;
    uint32_t required_bytes     = required_halfwords * 2;

    if((current_addr+required_bytes)>FLASH_USER_DATA_END_ADDR){
        /* Erase all the pages to fit data*/
        status = Flash_Memory_Erase_Pages(FLASH_USER_DATA_START_ADDR, FLASH_USER_DATA_NUM_PAGES);
        if(status != FLASH_OK){
            return status;
        }
        current_addr = FLASH_USER_DATA_START_ADDR;
        next_flash_write_addr = FLASH_USER_DATA_START_ADDR;
    }

    status = Flash_Memory_Unlock();
    if(status != FLASH_UNLOCKED){
        return status;
    }

    /* Program or store the user data*/
    for(uint32_t i=0;i<required_halfwords;i++){
        uint16_t halfword_data;

        /* Check if there are at least two bytes for half-word*/
        if(i * 2 + 1 < size){
            halfword_data = (uint16_t)Data[i*2] | ((uint16_t)Data[i*2+1]<<8);
        }else{ // Last half-word, possibly with only one byte
            halfword_data = (uint16_t)Data[i*2] | 0xFF00 ;
        }

        status = Flash_Program_Halfword(current_addr, halfword_data);
        if(status!=FLASH_OK){
            Flash_Memory_Lock();
            return status;
        }
        current_addr += sizeof(uint16_t);
    }
    next_flash_write_addr = current_addr;
    Flash_Memory_Lock();
    return FLASH_OK;
}

/* For Debugging purpose*/
uint32_t Flash_Get_Current_Write_Addr(void){
    return next_flash_write_addr;
}