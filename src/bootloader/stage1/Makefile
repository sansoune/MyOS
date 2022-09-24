build_dir?=build/
ASM?=nasm

.PHONY: all clean

all: stage1

stage1: $(build_dir)/stage1.bin

$(build_dir)/stage1.bin:
	$(ASM) boot.asm -f bin -o $(build_dir)/stage1.bin

clean:
	rm -f $(build_dir)/stage1.bin