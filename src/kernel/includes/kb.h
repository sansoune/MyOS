#include "stdio.h"
#include "io.h"
#include "../CPU/Interrupts/irq.h"


extern int status;


char* readStr();
void keyboard_callback(Registers* regs);
void init_kb();
void clean_buffer();
void curretnPos();
