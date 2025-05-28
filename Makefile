C_SOURCES = $(wildcard kernel/*.c kernel/libs/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h kernel/libs/*.h drivers/*.h)

# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o}

# Change this if your cross-compiler is somewhere else
CC = /usr/local/i686-elf/bin/i686-elf-gcc
GDB = /usr/local/i686-elf/bin/i686-elf-gdb
LD = /usr/local/i686-elf/bin/i686-elf-ld

# -g: Use debugging symbols in gcc
CFLAGS = -g

# First rule is run by default
yumeX-image: boot/bootsect.bin kernel.bin
	cat $^ > yumeX-image

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ 

run: yumeX-image
	qemu-system-i386 -fda yumeX-image

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o yumeX-image *.elf
	rm -rf kernel/*.o kernel/libs/*.o boot/*.bin drivers/*.o boot/*.o