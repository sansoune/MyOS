#pragma once
#include "stdint.h"

void print(const char* str);
void putc(char c);
void clear();
void setCursorPosition(uint16_t position);
uint16_t PostionFromCoords(uint8_t x, uint8_t y);
uint16_t GetCursorPos();
