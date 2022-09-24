#include "include/io.h"
#include "include/stdint.h"

void outb(int16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port) {
    uint8_t returnVal;
    asm volatile ("inb %1, %0" : "=a"(returnVal) : "Nd"(port));
    return returnVal;
}