MEMORY{
    flash (rx) : ORIGIN = 0x08000000, LENGTH = 1M
    sram1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K
    sram2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K
}

/* On utilise ces commandes pour linker image.raw en format binaire, que l'on met dans rodata après */
TARGET(binary) 
INPUT(./image.raw)
OUTPUT_FORMAT(default)

ENTRY(_start)

SECTIONS
{
    .vec_table : {
        *(.vec_table)
    } > flash

    .text : {
        *(.text)
    } > flash
    

    .data : {
        __data_start = .;
        *(.data)
        __data_end = .;
    } > sram1 AT > flash
 
    .rodata :{
        image = .;
        ./image.raw
        *(.rodata)
    } > flash

    .bss : {
        __bss_start = .;
        *(.bss) *(COMMON)
        __bss_end = .;
    } > sram1
}

_stack_start = ORIGIN(sram2) + LENGTH(sram2);
_start_data_flash = LOADADDR(.data);