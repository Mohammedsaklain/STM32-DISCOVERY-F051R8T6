MEMORY
{
    RAM     (rwx) : ORIGIN = 0x20000000, LENGTH = 8*1024
    FLASH   (rx)  : ORIGIN = 0x08000000, LENGTH = 64*1024
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

/*
|----------0x20002000----------| => _stack_end
|                              |
|                              |
|                              |
|----------0x20001C00----------| => _stack_begin (stack grows downwords from here)
|                              |
|        1024 - 1KB size       |
|                              |
|----------0x20000000----------| => ORIGIN(RAM)
*/