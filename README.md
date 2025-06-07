# yumeX OS

!!! The project has not been completed yet...

yumeX Hello World:

<img src="attachments/png/yumeX.png" alt="" width="600">

## How to run:
```
make run
```

### Dependencies:
1) qemu

If you own a linux distribution, try the following commands:

```
qemu-system-x86_64 -fda yumeX.img
```

or

```
kvm -fda yumeX.img
```

## How to build:
```
make build
```

### Dependencies:
1) i686-elf-gcc
2) i686-elf-ld

## GCC Cross Compiler osdev guide
- https://wiki.osdev.org/GCC_Cross-Compiler

## Links
- https://github.com/lukearend/x86-bootloader
- https://github.com/cfenollosa/os-tutorial