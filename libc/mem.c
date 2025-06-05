#include "types.h"

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
