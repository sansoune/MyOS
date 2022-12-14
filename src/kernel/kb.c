#include "includes/kb.h"
#include "utils/conversion.h"
#include "utils/types.h"
#include "utils/string.h"


static char buffer[256];
int status;
uint16_t curretPos;

const char scancode_to_char[] = {
    0, 0, '1','2','3', '4', '5', '6','7', '8', '9', '0', ')', '=',
    0, 0, 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$',
    0, 0, 'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', '%', '*',
    0, '<', 'w', 'x', 'c', 'v', 'b', 'n', ',', ';' ,':', '!',
};


char* readStr() {
     return buffer;
}

void clean_buffer() {
     buffer[0] = '\0';
}

void print_letter(uint8_t scancode) {
    switch (scancode)
    {
    case 0x01:
        print("esc");
        break;
    case 0x0E:
        //backspace
	    uint16_t pos = GetCursorPos();
	    if(pos > curretPos){
		    setCursorPosition(pos - 1);
        	print(" ");
       		setCursorPosition(pos - 1);
        	int len = strlen(buffer);
        	if(len > 0){
          		buffer[len - 1] = '\0';
        	}

	    }
        break;
    case 0x0F:
        print("    ");
	    append(buffer, ' ');
	    append(buffer, ' ');
	    append(buffer, ' ');
	    append(buffer, ' ');
        break;
    case 0x1C:
        print("\n");
	    append(buffer, '\n');
	//print(buffer);
	//buffer[0] = '\0';
	    status = false;
	//disable_kb();
        return;
    case 0x2A:
	    print("left shift");
	    break;
    case 0x39:
        print(" ");
	    append(buffer, ' ');
        break;
    default:
        //print(hex_to_String(scancode));
	    //print(kbdus[scancode]);
	    char letter = scancode_to_char[(int)scancode];
	    putc(letter);
	    append(buffer, letter);
        break;
    }
    return;
}

void keyboard_callback(Registers* regs) {
    uint8_t scancode = inb(0x60);
    if(scancode > 57) return;
    print_letter(scancode);
}

void curretnPos() {
    curretPos = GetCursorPos();
}

void init_kb(){
//    outb(0x21,0xfd);
//    outb(0xa1,0xff);
    IRQ_RegisterHandler(1, keyboard_callback);
    return;
}
