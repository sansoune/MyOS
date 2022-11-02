#include "includes/stdio.h"
#include "includes/io.h"
#include "utils/colors.h"
#include "utils/memory.h"

#define VGA_MEMORY (uint8_t*)0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

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

void clr_tty_line(int line){
	uint16_t index = PostionFromCoords(0, line);
	for(int i = 0; i < VGA_WIDTH; i++){
		*(VGA_MEMORY + index * 2) = 0;
		index++;
	}

}

int scroll_ln() {
     memcp((2 * PostionFromCoords(0, 1) + VGA_MEMORY), (2 * PostionFromCoords(0, 0) + VGA_MEMORY), VGA_WIDTH * (VGA_HEIGHT - 1) * 2);
     clr_tty_line(24);
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
   if(index >=  PostionFromCoords(VGA_WIDTH-1, VGA_HEIGHT-1)) {
	scroll_ln();
	index = index - 1 * VGA_WIDTH;
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
