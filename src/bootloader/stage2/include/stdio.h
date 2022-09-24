#pragma once
#include "stdint.h"

void setCursorPosition(uint16_t position);
uint16_t PositionFromCoords(uint8_t x, uint8_t y);
void print(const char* str);
