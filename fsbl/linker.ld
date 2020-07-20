MEMORY {
    SYSRAM (rwx)    :   ORIGIN = 0x2FFC2400, LENGTH = 256K
}

ENTRY(_start);

SECTIONS {
    .header : {
        FILL(0xFF);
        BYTE(0xFF);
        . = 0x100;
    } >SYSRAM

    .text : {
        *(.crt0)
        *(.text)
        *(.text*)

        KEEP(*(.init))
        KEEP(*(.fini))
    } >SYSRAM

    .rodata : {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } >SYSRAM

    .preinit_array : {
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
    } >SYSRAM

    .init_array : {
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
    } >SYSRAM

    .fini_array : {
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
    } >SYSRAM

    .data : {
        . = ALIGN(4);
        _data_begin_ = .;        
        *(.data)       
        *(.data*)        

        . = ALIGN(4);
        _data_end_ = .;   
    } >SYSRAM

    .bss : {
        . = ALIGN(4);
        _bss_start_ = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _bss_end_ = .;
    } >SYSRAM


}