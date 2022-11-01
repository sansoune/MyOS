

#include "includes/stdio.h"
#include "CPU/Interrupts/idt.h"
#include "CPU/Interrupts/isr.h"
#include "CPU/Interrupts/irq.h"
#include "CPU/Interrupts/gdt.h"
#include "includes/kb.h"
#include "utils/types.h"

void timer(Registers* regs) {
    print(".");
}

void start(void) {
    GDT_Init();
    IDT_INIT();
    isr_install();
    IRQ_INIT();
    char* buffer;
    //print("hello from c!\ntest 1234");
    //setCursorPosition(PostionFromCoords(20,9));
    //print("test hehehe hahaha");
    //IRQ_RegisterHandler(0, timer);
    init_kb();
    print("Welcome to San OS\n");
    while(true){
	status = true;
    	print("SANOS>");
	curretnPos();
   	while(status == true){
	//print(buffer);
	//buffer[0] = '\0';
    		buffer = readStr();
    	}
    	print(buffer);
	clean_buffer();
    }
    //IRQ_RegisterHandler(0, timer);
    // isr_registerhandler(33, keyboard_callback);
    // isr_registerhandler(32, timer);

    return;
}
