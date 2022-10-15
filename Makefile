ASM=nasm
GCC=x86_64-elf-gcc



all: img

build: clean
	$(ASM) ./src/bootloader/boot.asm -f bin -o ./build/boot.bin
	$(GCC) -g -ffreestanding -nostdlib -c ./src/kernel/main.c -o ./build/main.o 
	$(GCC) -g -ffreestanding -nostdlib -c ./src/kernel/stdio.c -o ./build/stdio.o
	$(GCC) -g -ffreestanding -nostdlib -c ./src/kernel/io.c -o ./build/io.o
	$(GCC) -g -ffreestanding -nostdlib -c ./src/kernel/CPU/Interrupts/idt.c -o ./build/idt.o
	$(GCC) -g -ffreestanding -nostdlib -c ./src/kernel/CPU/Interrupts/isr.c -o ./build/isr.o
	$(ASM) ./src/kernel/kernel.asm -f elf64 -o ./build/kernel.o
	$(ASM) ./src/kernel/CPU/Interrupts/interrupts.asm -f elf64 -o ./build/interrupts.o
	x86_64-elf-ld -o ./build/kernel.bin -T ./src/kernel/linker.ld -nostdlib ./build/kernel.o ./build/main.o ./build/stdio.o ./build/io.o ./build/idt.o ./build/isr.o ./build/interrupts.o
	cat ./build/boot.bin ./build/kernel.bin >> "./build/OS.bin"

img: build
	dd if=/dev/zero of=./build/main.img bs=512 count=2880
	dd if=./build/OS.bin of=./build/main.img conv=notrunc

clean:
	rm -rf ./build/*