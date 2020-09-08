#Utility

#BootLoader
boot0.bin: boot0.asm boot1.size 
	nasm -f bin boot0.asm -o boot0.bin

boot1.size: boot1.bin filesize.bin
	./filesize.bin $< $@

boot1.bin: boot1.asm main.size
	nasm -f bin boot1.asm -o boot1.bin

main.size: mainCPP.bin filesize.bin
	./filesize.bin $< $@


IMG_FILES= boot0.bin boot1.bin mainCPP.bin

a.img: makeboot.bin boot0.bin boot1.bin mainCPP.bin
	touch $@
	sudo ./makeboot.bin $@ $(IMG_FILES)

run: a.img
	qemu-system-i386 -hda a.img -monitor stdio -m 4096



#Operating System
main.bin: main.c
	gcc -m32 -ffreestanding -c main.c -o main.o
	gcc -m32 -ffreestanding -c print.c -o print.o
	gcc -m32 -ffreestanding -c ports.c -o ports.o
	
	ld -melf_i386 -e main -T linker.ld -o main.bin main.o print.o ports.o setGDT.o
	#objcopy -R .note -R .comment -S -O binary main1.o main.bin

#-ffreestanding 
GPPPARAMS = -fpermissive -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore 
#Operating System
mainCPP.bin: kernel.cpp
	g++ $(GPPPARAMS) -c kernel.cpp -o kernel.o
	g++ $(GPPPARAMS) -c print.cpp -o print.o
	g++ $(GPPPARAMS) -c ports.cpp -o ports.o
	g++ $(GPPPARAMS) -c gdt.cpp -o gdt.o
	nasm -f elf setGDT.asm -o setGDT.o
	ld -melf_i386 -e main -T linker.ld -o mainCPP.bin kernel.o print.o ports.o gdt.o setGDT.o
	#objcopy -R .note -R .comment -S -O binary main1.o main.bin

	


makeboot.bin: makeboot.c
	gcc -o $@ $^

filesize.bin: filesize.c
	gcc -o $@ $^


.PHONY: clean
clean:
	rm -rf *.bin *.img *.size *.inc *.o