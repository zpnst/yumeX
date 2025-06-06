#ifndef LOGS_H
#define LOGS_H

const char *SHELL_HELP_MESSAGE = "Type something, it will go through the kernel\n"
        "Type END to halt the CPU\n"
        "Type HELP to see a manual\n"
        "Type YUMEX to draw yumeX logo\n> ";

void ker_init_log();
void draw_yumeX_logo();

#endif /** LOGS_H */