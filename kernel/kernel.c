#include "libs/logs.h"
#include "libs/utils.h"

void kermain() {

    ker_init_log();
    draw_yumeX_logo();

    /* Fill up the screen */
    int cnt = 11;
    for (int iter = 42; iter <= 46; iter += 1) {
        char str[255];
        int_to_ascii(iter, str);
        kprint_at(str, 0, cnt);
        cnt += 1;
    }

    kprint_at("This text forces the kernel to scroll. Row 0 will disappear.\n", 60, 16);

    isr_install();
    
    /* Test the interrupts */
    __asm__ __volatile__("int $0");
    __asm__ __volatile__("int $9");
    __asm__ __volatile__("int $32");
}