#include "types.h"

s32
strlen(char string[]) 
{
    s32 iter = 0;
    while (string[iter] != '\0') ++iter;
    return iter;
}

void 
reverse(char string[]) 
{
    s32 tmpr, iter, jter;
    for (iter = 0, jter = strlen(string)-1; iter < jter; iter += 1, jter -= 1) {
        tmpr = string[iter];
        string[iter] = string[jter];
        string[jter] = tmpr;
    }
}

void 
int_to_ascii(s32 number, char string[]) 
{
    s32 sign;
    if ((sign = number) < 0) {
        number = -number;
    }

    s32 iter = 0;
    do {
        string[iter++] = number % 10 + '0';
    } while ((number /= 10) > 0);

    if (sign < 0) string[iter++] = '-';
    string[iter] = '\0';

    reverse(string);
}

void
append(char string[], char number) 
{
    s32 len = strlen(string);
    string[len] = number;
    string[len+1] = '\0';
}

void 
backspace(char string[]) 
{
    s32 len = strlen(string);
    string[len-1] = '\0';
}

s32 
strcmp(char string1[], char string2[]) 
{
    s32 iter;
    for (iter = 0; string1[iter] == string2[iter]; iter++) {
        if (string1[iter] == '\0') return 0;
    }
    return string1[iter] - string2[iter];
}