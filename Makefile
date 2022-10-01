ASM=nasm
GCC=x86_64-elf-gcc

.PHONY: build

build: clean
	$(ASM) ./src/bootloader/boot.asm -f bin -o ./build/boot.bin
	$(GCC) -g -ffreestanding -nostdlib -c ./src/kernel/main.c -o ./build/main.o
	$(GCC) -g -ffreestanding -nostdlib -c ./src/kernel/stdio.c -o ./build/stdio.o
	$(GCC) -g -ffreestanding -nostdlib -c ./src/kernel/io.c -o ./build/io.o
	$(ASM) ./src/kernel/kernel.asm -f elf64 -o ./build/kernel.o
	x86_64-elf-ld -o ./build/kernel.bin -Ttext 0x1000 ./build/kernel.o ./build/main.o ./build/stdio.o ./build/io.o --oformat binary
	cat ./build/boot.bin ./build/kernel.bin >> "./build/OS.bin"

img:
	dd if=/dev/zero of=./build/main.img bs=512 count=2880
	dd if=./build/OS.bin of=./build/main.img conv=notrunc

clean:
	rm -rf ./build/*