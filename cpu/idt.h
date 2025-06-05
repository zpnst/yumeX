#ifndef IDT_H
#define IDT_H

#include "../libc/types.h"

/* Segment selectors */
#define KERNEL_CS 0x08

/*
+---------------------------+---------------------------+ ...
| IDT Entry 0               | IDT Entry 1               |
+---------------------------+---------------------------+ ...
| Offset (15..0)            | Offset (15..0)            |
| Segment Selector          | Segment Selector          |
| Reserved (0)              | Reserved (0)              |
| Type (Gate Type)          | Type (Gate Type)          |
| DPL (Descriptor Privilege | DPL (Descriptor Privilege |
| Level)                    | Level)                    |
| Present (P)               | Present (P)               |
| Offset (31..16)           | Offset (31..16)           | 
+---------------------------+---------------------------+  ... */

/* How every interrupt gate (handler) is defined */
typedef struct {
    u16 low_offset; /* Lower 16 bits of handler function address */
    u16 sel; /* Kernel segment selector */
    u8 always0;
    /* First byte
     * Bit 7: "Interrupt is present"
     * Bits 6-5: Privilege level of caller (0=kernel..3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" */
    u8 flags; 
    u16 high_offset; /* Higher 16 bits of handler function address */
} __attribute__((packed)) idt_gate_t ;

/* A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it */
typedef struct {
    u16 limit;
    u32 base;
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256

/* Functions implemented in idt.c */
void set_idt_gate(s32 n, u32 handler);
void set_idt();

#endif /** IDT_H */
