#include "includes/stdio.h"
#include "includes/io.h"
#include "includes/colors.h"

#define VGA_MEMORY (uint8_t*)0xb8000
#define VGA_WIDTH 80

uint16_t CursorPosition;

void setCursorPosition(uint16_t position) {

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((position >> 8) & 0xFF));

    CursorPosition = position;
}

uint16_t PostionFromCoords(uint8_t x, uint8_t y) {
    return y * VGA_WIDTH + x;
}

void print(const char* str) {
    uint8_t* charPtr = (uint8_t*)str;
    int index = 0;
    while (*charPtr != 0)
    {
        switch (*charPtr)
        {
        case 10:
            index += VGA_WIDTH;
            break;
        case 13:
            index -= index % VGA_WIDTH;
        
        default:
        
        *(VGA_MEMORY + index * 2) = *charPtr;
        index++;
           
        }
        charPtr++;
    }
    setCursorPosition(index);
    
}