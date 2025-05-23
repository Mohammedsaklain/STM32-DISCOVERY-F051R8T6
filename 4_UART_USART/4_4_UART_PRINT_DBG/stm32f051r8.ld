/* THIS LD SCRIPT IS UPDATED FOR USING STD LIBRARIES, NEED TO BE TESTED */

MEMORY
{
    RAM(rwx) : ORIGIN = 0x20000000, LENGTH = 8K
    FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 64K
}

SECTIONS
{
    /* Define the .init section and place it in FLASH */
    .init :
    {
        KEEP(*(.init))      /* Keep the .init section */
        KEEP(*(.init.*))    /* Keep any .init subsections */
    } > FLASH

    /* Define the .fini section and place it in FLASH, typically after .init */
    .fini :
    {
        KEEP(*(.fini))      /* Keep the .fini section */
        KEEP(*(.fini.*))    /* Keep any .fini subsections */
    } > FLASH

    .text :
    {
        . = ALIGN(4);
        KEEP(*(.interrupt_vector))
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH

    /* Define the .eh_frame section and place it in FLASH */
    .eh_frame :
    {
        KEEP(*(.eh_frame))
        KEEP(*(.eh_frame.*)) /* Also include subsections if any */
    } > FLASH

    /* Define the .ARM.exidx section and place it in FLASH */
    .ARM.exidx :
    {
        KEEP(*(.ARM.exidx))
        KEEP(*(.ARM.exidx.*)) /* Also include subsections if any */
    } > FLASH

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

    end = .;

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