#include "includes/stdio.h"
#include "includes/io.h"
#include "utils/colors.h"

#define VGA_MEMORY (uint8_t*)0xB8000
#define VGA_WIDTH 80

uint16_t CursorPosition = 0;

void setCursorPosition(uint16_t position) {
    if(position >= 0 && position < 2000) {
        outb(0x3D4, 0x0F);
        outb(0x3D5, (uint8_t)(position & 0xFF));
        outb(0x3D4, 0x0E);
        outb(0x3D5, (uint8_t)((position >> 8) & 0xFF));
        CursorPosition = position;
    }
    return;
}


uint16_t PostionFromCoords(uint8_t x, uint8_t y) {
    return y * VGA_WIDTH + x;
}

uint16_t GetCursorPos()
{
	uint16_t pos = 0;
	outb(0x3D4, 0x0F);
	pos |= inb(0x3D5);
	outb(0x3D4, 0x0E);
	pos |= ((uint16_t)inb(0x3D5)) << 8;
	return pos;
}

void putc(char c){
    uint16_t index = CursorPosition;
    switch (c)
        {
        case 10:
            index += VGA_WIDTH - index % VGA_WIDTH;
            break;
        default:

        *(VGA_MEMORY + index * 2) = c;
        // *(VGA_MEMORY_COLOR + index * 2) = BACKGROUND_BLINKINGRED | FOREGROUND_CYAN;   just to test the colors
        index++;
   }
   setCursorPosition(index);
}


void print(const char* str) {
    uint8_t* charPtr = (uint8_t*)str;
    while (*charPtr != 0)
    {
        putc(*charPtr);
        charPtr++;
    }


}
