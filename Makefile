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

# Open the connection to qemu and load our kernel-object file with symbols
debug: yumeX-image kernel.elf
	qemu-system-i386 -s -fda yumeX-image -d guest_errors,int &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

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
	rm -rf kernel/*.o boot/*.bin drivers/*.o libc/*.o boot/*.o x86/*.o kernel/includes/*.o kernel/tests/*.o