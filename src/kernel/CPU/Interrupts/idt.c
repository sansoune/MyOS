#include "idt.h"

typedef struct 			// IDT structure
{
	uint16_t BaseLow;
	uint16_t SegmentSelector;	
	uint8_t Reserved;	
	uint8_t Flags;	
	uint16_t BaseHigh;
} __attribute__((packed)) IDTEntry;

typedef struct 
{
    uint16_t Limit;
    IDTEntry* Ptr;
} __attribute__((packed)) IDTDescriptor;



IDTEntry g_idt[256];
IDTDescriptor g_IDTDescriptor = { sizeof(g_idt) - 1, g_idt};

extern void idt_load(IDTDescriptor* idtDescriptor);

void IDT_SetGate(int interrupt, void* base, uint16_t segmentDescriptor, uint8_t flags) {
    g_idt[interrupt].BaseLow = ((uint32_t)base) & 0xFFFF;
    g_idt[interrupt].SegmentSelector = segmentDescriptor;
    g_idt[interrupt].Reserved = 0;
    g_idt[interrupt].Flags = flags;
    g_idt[interrupt].BaseHigh = ((uint32_t)base >> 16) & 0xFFFF;
}

void IDT_EnableGate(int interrupt) {
    FLAG_SET(g_idt[interrupt].Flags, IDT_FLAG_PRESENT);
}

void IDT_DisableGate(int interrupt) {
    FLAG_UNSET(g_idt[interrupt].Flags, IDT_FLAG_PRESENT);
}

void IDT_INIT() {
    idt_load(&g_IDTDescriptor);
}
