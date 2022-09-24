build_dir?=build/
ASM?=nasm
ASMFLAGS?= -f elf64
CC=x86_64-elf-gcc
CFLAGS?= -std=c99 -g -ffreestanding -nostdlib
LD?=ld


SOURCES_C=$(wildcard *.c)
SOURCES_ASM=$(wildcard *.asm)
OBJECTS_C=$(patsubst %.c, $(build_dir)/stage2/c/%.obj, $(SOURCES_C))
OBJECTS_ASM=$(patsubst %.asm, $(build_dir)/stage2/asm/%.obj, $(SOURCES_ASM))

.PHONY: all stage2 clean

all: stage2

stage2: $(build_dir)/stage2.bin

$(build_dir)/stage2.bin: $(OBJECTS_ASM) $(OBJECTS_C)
	x86_64-elf-ld -T linker.ld -nostdlib -o $@ $^ 



$(build_dir)/stage2/c/%.obj: %.c always
	$(CC) $(CFALGS) -c -o $@ $<

$(build_dir)/stage2/asm/%.obj: %.asm always
	$(ASM) $(ASMFLAGS) -o $@ $<

always:
	mkdir -p $(build_dir)/stage2/c
	mkdir -p $(build_dir)/stage2/asm

clean:
	rm -f $(build_dir)/satge2.bin

