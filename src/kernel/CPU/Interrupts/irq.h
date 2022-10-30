#pragma once
#include "isr.h"

typedef void (*IRQHandler)(Registers* regs);

extern void EnableInterrupts();

void IRQ_INIT();
void IRQ_RegisterHandler(int irq, IRQHandler handler);