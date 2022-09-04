ASM=nasm

src_dir=src
build_dir=build

.PHONY: all floppy_image kernel bootloader clean always

floppy_image: $(build_dir)/main.img

$(build_dir)/main.img: bootloader kernel
	dd if=/dev/zero of=$(build_dir)/main.img bs=512 count=2880
	mkfs.fat -F 12 -n "NBOS" $(build_dir)/main.img
	dd if=$(build_dir)/bootloader.bin of=$(build_dir)/main.img conv=notrunc
	mcopy -i $(build_dir)/main.img $(build_dir)/kernel.bin "::kernel.bin"

bootloader: $(build_dir)/bootloader.bin

$(build_dir)/bootloader.bin: always
	$(ASM) $(src_dir)/bootloader/boot.asm -f bin -o $(build_dir)/bootloader.bin

kernel: $(build_dir)/kernel.bin

$(build_dir)/kernel.bin: always
	$(ASM) $(src_dir)/kernel/main.asm -f bin -o $(build_dir)/kernel.bin

always: 
	mkdir -p $(build_dir)

clean:
	rm -rf $(build_dir)/*