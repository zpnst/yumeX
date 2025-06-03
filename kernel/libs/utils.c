#include "types.h"

void int_to_ascii(int number, char string[]) {
    s32 sign;
    if ((sign = number) < 0) {
        number = -number;
    } 

    s32 snumber = number;
    s32 digcnt = 0;
    while ((number /= 10) > 0) {
        digcnt += 1;
    }
    number = snumber;
         
    if (sign < 0) {
        digcnt += 1;
    }

    do {
        string[digcnt--] = number % 10 + '0';
    } while ((number /= 10) > 0);

    if (sign < 0) {
        string[digcnt--] = '-';
    }
    
    string[digcnt] = '\0';
}

/* Copy bytes from one place to another. */
void memory_copy(char *src, char *dest, s32 no_bytes) {
    s32 iter;
    for (iter = 0; iter < no_bytes; iter++) {
        *(dest + iter) = *(src + iter);
    }
}

void memory_set(u8 *dest, u8 val, u32 len) {
    u8 *temp = (u8*)dest;
    for (; len != 0; len--) {
        *temp++ = val;
    }
}
