#include "../../drivers/screen.h"

const char *strip = "----------------------------------------------------------------------------";
const char *message = "The kernel yumeX was successfully loaded in 32-bit protected mode.";

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
    kprint((char*)strip);
    kprint("\n");
    kprint((char*)message);
    kprint("\n");
    kprint((char*)strip);
    kprint("\n\n");
}