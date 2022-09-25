ASM=nasm
GCC=x86_64-elf-gcc

.PHONY: build

build:
	$(ASM) ./src/bootloader/boot.asm -f bin -o ./build/boot.bin
	$(GCC) -std=c99 -g -ffreestanding -nostdlib -c ./src/kernel/main.c -o ./build/main.o
	$(ASM) ./src/kernel/kernel.asm -f elf64 -o ./build/kernel.o
	x86_64-elf-ld -o ./build/kernel.bin -Ttext 0x1000 ./build/kernel.o ./build/main.o --oformat binary