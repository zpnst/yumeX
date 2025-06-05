#include "../libc/string.h"

#include "../drivers/timer.h"
#include "../drivers/keyboard.h"

#include "./includes/logs.h"

#include "./tests/basic_tests.h"

void kermain() {
    ker_init_log();
    draw_yumeX_logo();

    isr_install();
    irq_install();

    kprint("Type something, it will go through the kernel\n"
        "Type END to halt the CPU\n> ");
}

void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    } else if (strcmp(input, "YUMEX") == 0) {
        draw_yumeX_logo();
        kprint("\n> ");
    } else if (strcmp(input, "") == 0) {
        kprint(">");
    } else {
        kprint("You said: ");
        kprint(input);
        kprint("\n> ");
    }
}
