#include "includes/stdio.h"
#include "CPU/Interrupts/idt.h"
#include "CPU/Interrupts/isr.h"
#include "CPU/Interrupts/irq.h"
#include "CPU/Interrupts/gdt.h"
#include "includes/kb.h"

void timer(Registers* regs) {
    print(".");
}

void start(void) {
    GDT_Init();
    IDT_INIT();
    isr_install();
    IRQ_INIT();
    print("hello from c!\ntest 1234");
    setCursorPosition(PostionFromCoords(20,9));
    print("test hehehe hahaha");
    IRQ_RegisterHandler(0, timer);
    init_kb();
    // isr_registerhandler(33, keyboard_callback);
    // isr_registerhandler(32, timer);
    
    

    return;
}
