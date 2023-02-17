#include "memory.h"



void memcp(uint8_t* source, uint8_t* dest,  int count) {
      for (int i = 0; i < count; i++){
	      *(dest + i) = *(source + i);
      }
}

// extern void DetectMemory();
// extern uint8_t MemoryRegionCount;

void init_memory() {
      // return MemoryRegionCount;
}