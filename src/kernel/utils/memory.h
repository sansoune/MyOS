#pragma once
#include "../includes/stdint.h"

struct MemoryMapEntry
{
    uint64_t BaseAddress;
    uint64_t RegionLength;
    uint32_t RegionType;
    uint32_t ACPI;
};




void memcp(uint8_t* source, uint8_t* dest, int count);
void init_memory();
