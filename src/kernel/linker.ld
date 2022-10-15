ENTRY(entry)
OUTPUT_FORMAT("binary")

SECTIONS {
    . = 0x1000;
    .text : ALIGN(0x200) { __text_start = .;        *(.text) }
    .data : ALIGN(0x200) { __data_start = .;        *(.data) }
    .rodata : ALIGN(0x200) { __rodata_start = .;    *(.rodata) }
    .bss : ALIGN(0x200) { __bss_start = .;          *(.bss) }

    __end = .;
}