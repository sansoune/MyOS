ENTRY(entry)
OUTPUT_FORMAT("binary")

SECTIONS {
    . = 1M;
    .text :
   {  
       *(.text)
   }
   .data : { *(.data) }
   .bss  : { *(.bss)  }
}