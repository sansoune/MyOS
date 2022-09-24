bits 16
section .entry

extern __bss_start
extern __end

extern start
global entry

entry:
    cli
    mov [g_BootDrive], dl


    mov ax, ds
    mov ss, ax
    mov sp, 0xFFF0
    mov bp, sp

    
    call EnableA20          
    call LoadGDT            

    
    mov eax, cr0
    or al, 1
    mov cr0, eax

    
    jmp dword 08h:.pmode

.pmode:
    
    [bits 32]
    
    ; 6 - setup segment registers
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
   
    
    mov edi, __bss_start
    mov ecx, __end
    sub ecx, edi
    mov al, 0
    cld
    rep stosb

    
    xor edx, edx
    mov dl, [g_BootDrive]
    push edx
    call start

    cli
    hlt

EnableA20:
    [bits 16]
    
    call A20WaitInput
    mov al, KbdControllerDisableKeyboard
    out KbdControllerCommandPort, al

    
    call A20WaitInput
    mov al, KbdControllerReadCtrlOutputPort
    out KbdControllerCommandPort, al

    call A20WaitOutput
    in al, KbdControllerDataPort
    push eax

    
    call A20WaitInput
    mov al, KbdControllerWriteCtrlOutputPort
    out KbdControllerCommandPort, al
    
    call A20WaitInput
    pop eax
    or al, 2                                    
    out KbdControllerDataPort, al

    
    call A20WaitInput
    mov al, KbdControllerEnableKeyboard
    out KbdControllerCommandPort, al

    call A20WaitInput
    ret


A20WaitInput:
    [bits 16]
    
    in al, KbdControllerCommandPort
    test al, 2
    jnz A20WaitInput
    ret

A20WaitOutput:
    [bits 16]
    in al, KbdControllerCommandPort
    test al, 1
    jz A20WaitOutput
    ret


LoadGDT:
    [bits 16]
    lgdt [g_GDTDesc]
    ret

KbdControllerDataPort               equ 0x60
KbdControllerCommandPort            equ 0x64
KbdControllerDisableKeyboard        equ 0xAD
KbdControllerEnableKeyboard         equ 0xAE
KbdControllerReadCtrlOutputPort     equ 0xD0
KbdControllerWriteCtrlOutputPort    equ 0xD1

ScreenBuffer                        equ 0xB8000

g_GDT:      
            dq 0

            
            dw 0FFFFh                   
            dw 0                        
            db 0                        
            db 10011010b                
            db 11001111b                
            db 0                        

           
            dw 0FFFFh                   
            dw 0                        
            db 0                        
            db 10010010b               
            db 11001111b                
            db 0                       

            
            dw 0FFFFh                  
            dw 0                        
            db 0                        
            db 10011010b                
            db 00001111b                
            db 0                        

            
            dw 0FFFFh                   
            dw 0                       
            db 0                        
            db 10010010b                
            db 00001111b                
            db 0                        

g_GDTDesc:  dw g_GDTDesc - g_GDT - 1    
            dd g_GDT                    
            
g_BootDrive: db 0
