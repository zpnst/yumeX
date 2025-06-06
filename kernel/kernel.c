#include "../libc/string.h"

#include "../drivers/timer.h"
#include "../drivers/keyboard.h"

#include "./includes/logs.h"

#include "./tests/basic_tests.h"

void kermain() {
    /** init interrupts */
    isr_install();
    irq_install();
    
    /** kernel init messages */
    ker_init_log();
    draw_yumeX_logo();
    ker_init_help();
}

void user_input(char *input) {
    if (strcmp(input, "HALT") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        __asm__ __volatile__("hlt");
    } else if (strcmp(input, "YUMEX") == 0) {
        draw_yumeX_logo();
        kprint("\n> ");
    } else if (strcmp(input, "HELP") == 0) {
        ker_init_help();
    } else if (strcmp(input, "") == 0) {
        kprint(">");
    } else {
        kprint("Echo: ");
        kprint(input);
        kprint("\n> ");
    }
}
