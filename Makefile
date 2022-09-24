ASM=nasm
CC=x86_64-elf-gcc
LD=ld 
src_dir=src
build_dir=build

.PHONY: all floppy_image kernel bootloader clean always

floppy_image: $(build_dir)/main.img

$(build_dir)/main.img: bootloader kernel
	dd if=/dev/zero of=$(build_dir)/main.img bs=512 count=2880
	mkfs.fat -F 12 -n "NBOS" $(build_dir)/main.img
	dd if=$(build_dir)/stage1.bin of=$(build_dir)/main.img conv=notrunc
	mcopy -i $(build_dir)/main.img $(build_dir)/stage2.bin "::stage2.bin"
	mcopy -i $(build_dir)/main.img $(build_dir)/kernel.bin "::kernel.bin"

bootloader: stage1 satge2


stage1: $(build_dir)/stage1.bin

$(build_dir)/stage1.bin: always
	$(MAKE) -C $(src_dir)/bootloader/stage1 build_dir=$(abspath $(build_dir))

satge2: $(build_dir)/stage2.bin

$(build_dir)/stage2.bin: always
	$(MAKE) -C $(src_dir)/bootloader/stage2 build_dir=$(abspath $(build_dir))


kernel: $(build_dir)/kernel.bin

$(build_dir)/kernel.bin: always
	$(ASM) $(src_dir)/kernel/main.asm -f bin -o $(build_dir)/kernel.bin

always: 
	mkdir -p $(build_dir)

clean:
	rm -rf $(build_dir)/*
