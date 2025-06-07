#include "basic_tests.h"

#include "../../x86/isr.h"

#include "../../libc/string.h"

#include "../../drivers/timer.h"
#include "../../drivers/screen.h"

#include "../../kernel/includes/logs.h"

void 
test_IO() 
{
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
}

void 
test_INT()
{
    isr_install();

    /* Test the interrupts */
    __asm__ __volatile__("int $0");
    __asm__ __volatile__("int $9");
    __asm__ __volatile__("int $32");
}

void 
test_Timer() 
{
    init_timer(50);
}