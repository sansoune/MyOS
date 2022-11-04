#include "includes/stdio.h"
#include "CPU/Interrupts/idt.h"
#include "CPU/Interrupts/isr.h"
#include "CPU/Interrupts/irq.h"
#include "CPU/Interrupts/gdt.h"
#include "CPU/timer/timer.h"
#include "includes/kb.h"
#include "utils/types.h"
#include "shell/shell.h"

void start(void) {
    GDT_Init();
    IDT_INIT();
    isr_install();
    IRQ_INIT();
    char* buffer;
    init_timer();
    init_kb();
    print("Welcome to San OS\n");
    while(true){
	status = true;
    	print("SANOS>");
	curretnPos();
   	while(status == true){
    	    buffer = readStr();
    	}
    	shell(buffer);
	clean_buffer();
    }
    return;
}
