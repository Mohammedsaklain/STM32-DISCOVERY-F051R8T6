/* file:        stm32f051r8.ld */
/* Modified On: 27/05/25       */

MEMORY
{
    RAM             (rwx)   : ORIGIN = 0x20000000, LENGTH = (8*1024)
    FLASH_CODE      (rx)    : ORIGIN = 0x08004000, LENGTH = (44*1024)
    FLASH_USER_DATA (rwx)   : ORIGIN = 0x0800F000, LENGTH = (4*1024) /* 4 pages = 4KB */
}

SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        KEEP(*(.interrupt_vector))
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH_CODE

    /* .init usually contains code that needs to be executed once */
    /* Explicitly place .init section immediately after .text in FLASH, */
    /* The linker often automatically creates an implicit .init section & adds after .text section */

    .init :
    {
        . = ALIGN(4);
        KEEP(*(.init))   /* Standard .init section */
        KEEP(*(.init.*))
        . = ALIGN(4);
    } > FLASH_CODE

    /* Contains code for global destructors */
    .fini :
    {
        . = ALIGN(4);
        KEEP(*(.fini))
        KEEP(*(.fini.*))
        . = ALIGN(4);
    } > FLASH_CODE

    /* This section contains information used for unwinding the stack ,*/
    /* primarily for C++ exception handling and sometimes for debugging */
    .eh_frame :
    {
        . = ALIGN(4);
        KEEP(*(.eh_frame))
        KEEP(*(.eh_frame.*))
        . = ALIGN(4);
    } > FLASH_CODE

    /* .ARM.extab and .ARM.exidx are ARM-specific exception handling tables */
    .ARM.extab :
    {
        . = ALIGN(4);
        *(.ARM.extab*)
        . = ALIGN(4);
    } > FLASH_CODE

    .ARM.exidx :
    {
        . = ALIGN(4);
        *(.ARM.exidx*)
        . = ALIGN(4);
    } > FLASH_CODE

    _data_flash = .;
    .data : AT ( _data_flash )
    {
        . = ALIGN(4);
        _data_begin = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _data_end = .;
    } > RAM

    .bss :
    {
        _bss_begin = .;
        __bss_start__ = _bss_begin;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _bss_end = .;
        __bss_end__ = _bss_end;
    } > RAM

    /* .heap section */
    .heap (NOLOAD) :
    {
        . = ALIGN(8);
        _heap_start = .;    /* Symbol for start of heap */
        . = . + 0x200;      /* Reserve 512 bytes for heap */
        . = ALIGN(8);
        _heap_end = .;      /* Symbol for end of heap */
    } > RAM

    /* tells the linker not to load any actual data into this section from compiled firmware */
    .user_flash_data (NOLOAD) :
    {
        . = ALIGN(4);
        __flash_user_data_start__ = .;      /* symbol for start address */
        . = . + LENGTH(FLASH_USER_DATA);
        __flash_user_data_end__ = .;        /* symbol for End address */
    } >FLASH_USER_DATA

    _stack_size = 1024;
    _stack_end = ORIGIN(RAM)+LENGTH(RAM);
    _stack_begin = _stack_end - _stack_size;
    . = _stack_begin;
    ._stack :
    {
        . = . + _stack_size;
    } > RAM
}

ENTRY(handler_reset)