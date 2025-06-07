#include "../../drivers/screen.h"

const char *STRIP = "----------------------------------------------------------------------------";
const char *MESSAGE = "The yumeX kernel was successfully loaded in 32-bit protected mode.";

const char *SHELL_HELP_MESSAGE = 
        "Type \"HALT\" to halt the CPU\n"
        "Type \"HELP\" to see the manual.\n"
        "Type \"YUMEX\" to draw the yumeX logo.\n> ";

void draw_yumeX_logo() {
    kprint("                              _  __    ____  _____\n");
    kprint("   __  ____  ______ ___  ___ | |/ /   / __ \\/ ___/\n");
    kprint("  / / / / / / / __ `__ \\/ _ \\|   /   / / / /\\__ \\\n");
    kprint(" / /_/ / /_/ / / / / / /  __/   |   / /_/ /___/ /\n");
    kprint(" \\__, /\\__,_/_/ /_/ /_/\\___/_/|_|   \\____//____/\n");
    kprint("/____/\n");
    kprint("\n");
}

void ker_init_log() {
    clear_screen();
    kprint((char*)STRIP);
    kprint("\n");
    kprint((char*)MESSAGE);
    kprint("\n");
    kprint((char*)STRIP);
    kprint("\n\n");
}

void ker_init_help() {
    kprint((char *)SHELL_HELP_MESSAGE);
}