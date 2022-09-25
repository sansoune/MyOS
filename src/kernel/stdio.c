#include "includes/stdio.h"

#define VGA_MEMORY (uint8_t*)0xb8000

void print(const char* str) {
    uint8_t* charPtr = (uint8_t*)str;
    uint16_t index = 0;
    while (*charPtr != 0)
    {
        *(VGA_MEMORY + index *2) = *charPtr;
        index++;
        charPtr++;
    }
    
}