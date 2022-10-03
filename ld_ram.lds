MEMORY{
    flash (rx) : ORIGIN = 0x08000000, LENGTH = 1M
    sram1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K
    sram2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K
}

ENTRY(_start)

SECTIONS
{
    .text : {
        *(.text)
    } > sram1
 
    .rodata :{
        *(.rodata)
    } > sram1
    
    .data : {
        *(.data)
    } > sram1
 
    .bss : {
        __bss_start = .;
        *(.bss) *(COMMON)
        __bss_end = .;
    } > sram1
}

_stack_start = ORIGIN(sram2) + LENGTH(sram2);
