


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
    case 0x03:
        print("2");
        break;
    case 0x04:
        print("3");
        break;
    case 0x05:
        print("4");
        break;
    case 0x06:
        print("5");
        break;
    case 0x07:
        print("6");
        break;
    case 0x08:
        print("7");
        break;
    case 0x09:
        print("8");
        break;
    case 0x0A:
        print("9");
        break;
    case 0x0B:
        print("0");
        break;
    case 0x0C:
        print(")");
        break;
    case 0x0D:
        print("=");
        break;
    case 0x0E:
        //backspace
	setCursorPosition(GetCursorPos() - 1);
	print(" ");
	setCursorPosition(GetCursorPos() - 1);
        break;
    case 0x0F:
        print("    ");
        break;
    case 0x10:
        print("a");
        break;
    case 0x11:
        print("z");
        break;
    case 0x12:
        print("e");
        break;
    case 0x13:
        print("r");
        break;
    case 0x14:
        print("t");
        break;
    case 0x15:
        print("y");
        break;
    case 0x16:
        print("u");
        break;
    case 0x17:
        print("i");
        break;
    case 0x18:
        print("o");
        break;
    case 0x19:
        print("p");
        break;
    case 0x1A:
        print("^");
        break;
    case 0x1B:
        print("$");
        break;
    case 0x1C:
        print("\n");
        break;
    case 0x1E:
        print("q");
        break;
    case 0x1F:
        print("s");
        break;
    case 0x20:
        print("d");
        break;
    case 0x21:
        print("f");
        break;
    case 0x22:
        print("g");
        break;
    case 0x23:
        print("h");
        break;
    case 0x24:
        print("j");
        break;
    case 0x25:
        print("k");
        break;
    case 0x26:
        print("l");
        break;
    case 0x27:
        print("m");
        break;
    case 0x28:
        print("ù");
        break;
    case 0x29:
        print("*");
        break;
    case 0x2B:
        print("<");
        break;
    case 0x2C:
        print("w");
        break;
    case 0x2D:
        print("x");
        break;
    case 0x2E:
        print("c");
        break;
    case 0x2F:
        print("v");
        break;
    case 0x30:
        print("b");
        break;
    case 0x31:
        print("n");
        break;
    case 0x32:
        print(",");
        break;
    case 0x33:
        print(";");
        break;
    case 0x34:
        print(":");
        break;
    case 0x35:
        print("!");
        break;
    case 0x39:
        print(" ");
        break;




    default:
        //print(hex_to_String(scancode));
	//print(kbdus[scancode]);
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
