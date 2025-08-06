C_SOURCES = $(wildcard kernel/*.c drivers/*.c libc/*.c kernel/includes/*.c kernel/tests/*.c x86/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h libc/*.h kernel/includes/*.h kernel/tests/*.h x86/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o x86/interrupt.o} 

# Change this if your cross-compiler is somewhere else
CC = /usr/local/i686-elf/bin/i686-elf-gcc
GDB = /usr/local/i686-elf/bin/i686-elf-gdb
LD = /usr/local/i686-elf/bin/i686-elf-ld

# -g: Use debugging symbols in gcc
CFLAGS = -g

# First rule is run by default
yumeX.img: boot/bootsect.bin kernel.bin
	cat $^ > yumeX.img

yumeX.vdi: yumeX.img
	truncate -s 1474560 yumeX.img
	VBoxManage convertfromraw yumeX.img yumeX.vdi --format VDI

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

build: yumeX.img

run:
	qemu-system-i386 -fda yumeX.img

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o libc/*.o boot/*.o x86/*.o kernel/includes/*.o kernel/tests/*.o

cleani:
	rm yumeX.img yumeX.vdi