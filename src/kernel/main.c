#include "includes/stdio.h"
#include "CPU/Interrupts/idt.h"

void start(void) {
    IDT_INIT();
    print("hello from c!\ntest 1234");
    // setCursorPosition(PostionFromCoords(0,0)); commented for some bugs will be fixed later
    return;
}