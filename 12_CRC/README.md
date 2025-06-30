# STM32F051 Hardware CRC Driver

A simple and efficient C driver for the hardware Cyclic Redundancy Check (CRC) unit on the STM32F051 microcontroller. This CRC driver provides a clear, minimal example of how to use the built-in CRC peripheral for data integrity checks.

---

## 🛠️ Hardware Requirements

* **Microcontroller**: STM32F051 series (or any STM32 with a compatible CRC unit).
* **Development Board**: Any board with an STM32F051, such as the STM32F0 Discovery Kit.

---

## 🔧 How to Use

### 1. File Structure

Integrate the `crc.c` and `crc.h` files into your project's source code. You will also need your microcontroller's header file (`stm32f0xx.h` or similar), which provides the register definitions.

### 2. Initialization

Before calculating any CRCs, you must initialize the CRC peripheral. This involves enabling its clock and resetting its internal state.

```c
#include "crc.h"
int main(void) {
    // ...
    CRC_Init(); // This enables the clock and resets the CRC unit
    // ...
    while(1) {
        // ...
    }
}
```

### 3. Output

The function ***CRC_Calculate_32B*** returns the 32 bit CRC output. 

```C
    Result = CRC_Calculate_32B();
```

***NOTE:*** We can validate the calculated CRC from C code provided in the unit test folder. 