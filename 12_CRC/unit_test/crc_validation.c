/* To calculate the CRC at host end */

#include <stdio.h>
#include <stdint.h>

#define CRC32_POLYNOMIAL    0x04C11DB7

uint32_t calculate_crc32_word(uint32_t input_data) {
    uint32_t crc_register = 0xFFFFFFFF; // Initial value for the CRC register
    uint32_t temp_data = input_data;
    uint8_t bit_index;

    crc_register ^= temp_data;

    for (bit_index = 0; bit_index < 32; bit_index++) {
        
        if ((crc_register & 0x80000000) != 0) {
            // If MSB is 1, shift left and XOR with the polynomial
            crc_register = (crc_register << 1) ^ CRC32_POLYNOMIAL;
        } else {
            // If MSB is 0, just shift left
            crc_register <<= 1;
        }
    }
    return crc_register;
}

int main(void) {
    uint32_t input_data = 0xCC;//0xDEADBEEF;
    uint32_t crc_result = calculate_crc32_word(input_data);
    
    printf("Input Data: 0x%08X\n", input_data);
    printf("Calculated CRC-32: 0x%08X\n", crc_result);
    return 0;
}