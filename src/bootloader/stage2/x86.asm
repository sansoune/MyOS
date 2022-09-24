bits 16

section .text

; global x86_Video_WriteCharTeletype
; x86_Video_WriteCharTeletype:
;     push bp
;     mov bp, sp

;     push bx

;     mov ah, 0Eh
;     mov al, [bp + 4]
;     mov bh, [bp + 6]

;     int 10h

;     pop bx

;     mov sp, bp
;     pop bp
;     ret

global print
printy:
    push bp
    mov bp, sp

    push bx

    mov ah, 0x0e
    mov al, [bp - 4]
    int 10h
    
    pop bx
    mov sp, bp
    pop bp

    ret
