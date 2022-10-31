#include "irq.h"
#include "../../includes/pic.h"
#include "../../utils/types.h"
#include "../../utils/conversion.h"
#include "../../includes/io.h"

#define PIC_REMAP_OFFSET 0x20

IRQHandler g_IRQHandler[16];

void IRQ_Handler(Registers* regs) {
    int irq = regs->interrupt - PIC_REMAP_OFFSET; 

    uint8_t pic_isr = PIC_ReadInServiceRegister();
    uint8_t pic_irr = PIC_ReadIRQRequestRegister();

    if(g_IRQHandler[irq] != NULL) {
        g_IRQHandler[irq](regs);
    }else {
        print("Unhandeled irq");
        print(toString(irq));
    }

    PIC_SendEndOfInterrupt(irq);
}

void IRQ_INIT() {
    PIC_configure(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET + 8);

    for (int i = 0; i < 16; i++) {
        isr_registerhandler(PIC_REMAP_OFFSET + i, IRQ_Handler);
        
        
    }

    
    EnableInterrupts();
}


void IRQ_RegisterHandler(int irq, IRQHandler handler) {
    g_IRQHandler[irq] = handler;
}
