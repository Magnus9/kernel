
#ifndef INCLUDE_IDT_H
#define INCLUDE_IDT_H

#include <types.h>

#define IDT_PRESENT     0x01 << 7
#define IDT_DPL0        0x00 << 5
#define IDT_DPL1        0x01 << 5
#define IDT_DPL2        0x02 << 5
#define IDT_DPL3        0x03 << 5
#define IDT_INTERRUPT   0x0e
#define IDT_TRAP        0x0f

#define IDT_INTERRUPT_MASK      IDT_INTERRUPT | IDT_PRESENT
#define IDT_TRAP_MASK           IDT_TRAP | IDT_PRESENT

struct idt_base {
    u16 limit;
    u32 base;
} __attribute__ ((packed));

struct idt_descriptor {
    u16 off_low;
    u16 selector;
    u8 zero;
    u8 attr;
    u16 off_high;
};
void idt_init(void);
void idt_init_descriptor(struct idt_descriptor *desc,
                         u32 base);
void lidt(void *base);

#endif