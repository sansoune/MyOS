section .text
[bits 32]

extern start
extern __bss_start
extern __end

global entry
entry:
    mov edi, __bss_start
    mov ecx, __end
    mov ecx, __bss_start
    mov al, 0
    rep stosb

    ; push ebp
    ; mov ebp, esp

    ; mov eax, [ebp + 4]
    mov eax, [MEMORY_REGION_COUNT_LOCATION]
    push eax


    cli
    call start
    jmp $ 

MEMORY_REGION_COUNT_LOCATION equ 0x700