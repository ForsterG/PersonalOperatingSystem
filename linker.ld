ENTRY(main)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

SECTIONS
{
    . = 0x2000;
    .text :
    {
        
        *(.text*)
        *(.rodata)
    }
    .data :
    {
        *(.data)
    }
    .bss :
    {
        *(.bss)
    }
    /DISCARD/ :
    {
        *(.fini_array*)
        *(.comment)
        *(.note)
    }
}