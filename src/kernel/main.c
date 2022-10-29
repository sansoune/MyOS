#include "includes/stdio.h"
#include "CPU/Interrupts/idt.h"

void start(void) {
    IDT_INIT();
    print("hello from c!\ntest 1234");
    setCursorPosition(PostionFromCoords(20,9));
    print("test hehehe hahaha");
    return;
}