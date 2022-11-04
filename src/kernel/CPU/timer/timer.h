#pragma once
#include "../Interrupts/irq.h"
#include "../../includes/stdint.h"

void init_timer();
int second();
void sleep(int ticks);
