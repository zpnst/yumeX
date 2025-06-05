#ifndef STRING_H
#define STRING_H

#include "types.h"

s32 strlen(char string[]);
void reverse(char string[]);
void int_to_ascii(s32 number, char string[]);
void append(char string[], char number);
void backspace(char string[]);
int strcmp(char string1[], char string2[]);


#endif /** STRING_H */