[org 0x7c00]
[bits 16]
KERNEL_LOCATION equ 0x1000
MEMORY_REGION_COUNT_LOCATION equ 0x700

section .text
global start

start:
    mov [BOOT_DISK], dl

    xor ax, ax                          
    mov es, ax
    mov ds, ax
    mov bp, 0x9000
    mov sp, bp

    mov bx, KERNEL_LOCATION
    mov dh, 50

    mov ah, 0x02
    mov al, dh 
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    mov dl, [BOOT_DISK]
    int 0x13  

    mov ah, 0x0
    mov al, 0x3
    int 0x10

    call DetectMemory
    cli
    lgdt [GDT_Descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    mov eax, [MemoryRegionCount]
    mov [MEMORY_REGION_COUNT_LOCATION], eax

    jmp CODE_SEG:start_protected_mode
    jmp $

%include "./src/bootloader/memory.asm"

[bits 32]
start_protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    in al, 0x92
	or al, 0x02
	out 0x92, al

    jmp KERNEL_LOCATION


CODE_SEG equ code - GDT_Start
DATA_SEG equ data - GDT_Start

GDT_Start:
    null:
        dd 0x0
        dd 0x0
    
    code:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10011010
        db 0b11001111
        db 0x0
    
    data:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10010010
        db 0b11001111
        db 0X0

GDT_End:

GDT_Descriptor:
    dw GDT_End - GDT_Start - 1
    dd GDT_Start

BOOT_DISK: db 0

times 510-($-$$) db 0
dw 0AA55h
