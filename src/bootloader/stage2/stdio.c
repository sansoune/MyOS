
#include "include/stdio.h"
#include "include/stdint.h"
#include "include/io.h"

#define VGA_MEMORY (uint8_t*)0xb8000     
#define VGA_WIDTH 80

const unsigned SCREEN_HEIGHT = 25;
const uint8_t DEFAULT_COLOR = 0x7;

uint8_t CursorPostion;


void setCursorPosition(uint16_t position) {
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((position >> 8) & 0xFF));

    CursorPostion = position;
}

uint16_t PositionFromCoords(uint8_t x, uint8_t y) {
    return y * VGA_WIDTH + x;
}


void print(const char* str) {
    uint8_t* charPtr = (uint8_t*)str;
    uint16_t index = 0;
    while(*charPtr != 0){
        *(VGA_MEMORY + index * 2) = *charPtr;
        index = index + 1;
        charPtr = charPtr + 1;
    }
}



