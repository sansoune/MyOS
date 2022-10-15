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

    cli
    call start
    jmp $ 