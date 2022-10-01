#include "includes/io.h"

void outb(uint16_t port, uint8_t val){
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port) {
    uint8_t retVal;
    asm volatile ("inb %1, %0" : "=a"(retVal) : "Nd"(port));
    return retVal;
}