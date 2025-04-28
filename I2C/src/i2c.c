#include "main.h"

void i2c_init(void)
{
    I2C1->CR1 &= ~I2C_CR1_PE;    // First reset the I2C Peripheral
    I2C1->TIMINGR =0x0010020A;   // Configuring Timing Register as per CubeMX
    I2C1->CR1   |= I2C_CR1_PE;   // Enable I2C peripheral
}

void i2c_read(uint8_t slav_add, uint8_t memadd, uint8_t *data, uint8_t length )
{
    /*Sending Memory Address - Write Operation*/

    uint8_t I2C_CR2_NBYTES_Pos = length;    /* Number of Bytes to be Read/Write*/
	I2C1->CR1 |=I2C_CR1_PE;                 /*Enable I2C*/
	I2C1->CR2=(slav_add<<1);                /*Set slave address*/
	I2C1->CR2&=~I2C_CR2_ADD10;              /*7-bit addressing*/
	I2C1->CR2|=(1<<I2C_CR2_NBYTES_Pos);     /*Set number to transfer to 1 for write operation*/
	I2C1->CR2&=~I2C_CR2_RD_WRN;             /*Set the mode to write mode*/
	I2C1->CR2&=~I2C_CR2_AUTOEND;            /*Software end*/
	I2C1->CR2|=I2C_CR2_START;               /*Generate start*/

	/*Wait until transfer is completed*/
	while(!(I2C1->ISR & I2C_ISR_TC))
    {
		/*Check if TX buffer is empty*/
		if(I2C1->ISR & I2C_ISR_TXE)
		{
			I2C1->TXDR = (memadd);          /*send memory address*/
		}
	}

    /* Read Operation*/

	I2C1->CR1 &=~I2C_CR1_PE;                    /*Reset I2C*/
	I2C1->CR1 |=I2C_CR1_PE;
	I2C1->CR2=(slav_add<<1);                    /*Set slave address*/
	I2C1->CR2|=I2C_CR2_RD_WRN;                  /*Set mode to read operation*/
	I2C1->CR2|=((length)<<I2C_CR2_NBYTES_Pos);  /*Set length to the required length*/
	I2C1->CR2|=I2C_CR2_AUTOEND;                 /*aut generate stop after transfer completed*/
	I2C1->CR2|=I2C_CR2_START;                   /*Generate start*/

	/*wait until stop is generated*/
	while(!(I2C1->ISR & I2C_ISR_STOPF))
			{
				/*If RX buffer is empty*/
			  if(I2C1->ISR &(I2C_ISR_RXNE))
                {
				  *data++=I2C1->RXDR;
                }
			}
	I2C1->CR1 &=~I2C_CR1_PE;                    /*disable the peripheral*/
}
