#include "includes/kb.h"
#include "utils/conversion.h"

void print_letter(uint8_t scancode) {
    switch (scancode)
    {
    case 0x01:
        print("esc");
        break;
    case 0x02:
	print("1");
	break;
    default:
        print(hex_to_String(scancode));
        break;
    }
}

void keyboard_callback(Registers* regs) {
    uint8_t scancode = inb(0x60);
    print_letter(scancode);
}


void init_kb(){
    outb(0x21,0xfd);
    outb(0xa1,0xff);
    IRQ_RegisterHandler(1, keyboard_callback);
}
