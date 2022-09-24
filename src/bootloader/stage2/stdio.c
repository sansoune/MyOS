
#include "include/stdio.h"
#include "include/stdint.h"

#define VGA_MEMORY (uint8_t*)0xb8000

// extern void x86_Video_WriteCharTeletype(char c, uint8_t page);

const unsigned SCREEN_WIDTH = 80;
const unsigned SCREEN_HEIGHT = 25;
const uint8_t DEFAULT_COLOR = 0x7;


void print(const char* str) {
    uint8_t* charPtr = (uint8_t*)str;
    uint16_t index = 0;
    while(*charPtr != 0){
        *(VGA_MEMORY + index * 2) = *charPtr;
        index = index + 1;
        charPtr = charPtr + 1;
    }
}



