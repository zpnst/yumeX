#ifndef MEM_H
#define MEM_H

#include "types.h"

void memory_set(u8 *dest, u8 val, u32 len);
void memory_copy(char *source, char *dest, s32 no_bytes);

#endif /** MEM_H */