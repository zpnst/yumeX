#include "keyboard.h"
#include "screen.h"

#include "../x86/ports.h"
#include "../x86/isr.h"

#include "../libc/string.h"
#include "../libc/function.h"

#include "../kernel/includes/logs.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];

#define SC_MAX 57

const char sc_ascii[] = {
    '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
    'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
    'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
    'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '
};


void 
shell_input(char *input) 
{
    if (strcmp(input, "HALT") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        __asm__ __volatile__("hlt");
    } else if (strcmp(input, "YUMEX") == 0) {
        draw_yumeX_logo();
        kprint("\n> ");
    } else if (strcmp(input, "MAN") == 0) {
        ker_manual();
        kprint("\n> ");
    } else if (strcmp(input, "CLEAR") == 0) {
        clear_screen();
    } else if (strcmp(input, "") == 0) {
        kprint(">");
    } else {
        kprint("Echo: ");
        kprint(input);
        kprint("\n> ");
    }
}

static void 
keyboard_callback(registers_t regs) 
{
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = port_byte_in(0x60);
    
    if (scancode > SC_MAX) return;
    if (scancode == BACKSPACE) {
        backspace(key_buffer);
        kprint_backspace();
    } else if (scancode == ENTER) {
        kprint("\n");
        shell_input(key_buffer); /* kernel-controlled function */
        key_buffer[0] = '\0';
    } else {
        char letter = sc_ascii[(int)scancode];

        /* Remember that kprint only accepts char[] */
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kprint(str);
    }
    UNUSED(regs);
}

void 
init_keyboard() 
{
   register_interrupt_handler(IRQ1, keyboard_callback); 
}
