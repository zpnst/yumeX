#ifndef SCREEN_H
#define SCREEN_H

#include "../libc/types.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Attribute byte for our default colour scheme.
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

// Internal VGA regissters
#define CURSOR_HB 0x0E
#define CURSOR_LD 0x0F

// API
void clear_screen();
void kprint_backspace();
void kprint(char *message);
void kprint_at(char *message, s32 col, s32 row);

#endif /** SCREEN_H */