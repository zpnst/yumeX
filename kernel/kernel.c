#include "../x86/isr.h"
#include "../libc/string.h"
#include "../drivers/timer.h"
#include "../drivers/keyboard.h"

#include "./includes/logs.h"
#include "./tests/basic_tests.h"

void 
kermain() 
{
    /** init interrupts */
    isr_install();
    irq_install();
    
    /** kernel init messages */
    ker_init_log();
    draw_yumeX_logo();
    ker_shell_init_message();
}
