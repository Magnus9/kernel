
#ifndef INCLUDE_GDT_H
#define INCLUDE_GDT_H

#include <types.h>

#define GDT_NULL        0x00
#define GDT_KERN_CODE   0x01
#define GDT_KERN_DATA   0x02
#define GDT_USER_CODE   0x03
#define GDT_USER_DATA   0x04
#define GDT_TABLE_SIZE  0x05

/*
 * Defines the attributes for a segment
 * descriptor.
 */
#define GDT_PRESENT     0x01 << 7
#define GDT_DPL0        0x00 << 5
#define GDT_DPL1        0x01 << 5
#define GDT_DPL2        0x02 << 5
#define GDT_DPL3        0x03 << 5
#define GDT_SYSTEM      0x00 << 4
#define GDT_CODE_DATA   0x01 << 4
#define GDT_EXEC        0x01 << 3
#define GDT_CONFORMING  0x01 << 2
#define GDT_PRIVILEGE   0x01 << 1

/*
 * Defines the flags for a segment descriptor.
 */
#define GDT_GRAN        0x01 << 7
#define GDT_PROT_MODE   0x01 << 6
#define GDT_LONG_MODE   0x01 << 5

struct gdt_base {
    u16 limit;
    u32 base;
} __attribute__ ((packed));

struct gdt_descriptor {
    u16 limit_low;
    u16 base_low;
    u8 base_med;
    u8 access;
    u8 flags_limit_high;
    u8 base_high;
};
void gdt_init(void);
void gdt_init_descriptor(struct gdt_descriptor *desc,
                         u32 base, u32 limit, u8 access,
                         u8 flags);
void lgdt(struct gdt_base *base);
void sgdt(struct gdt_base *base);
void load_cs();
void load_ss(u16 selector);
void load_ds(u16 selector);
void load_es(u16 selector);
void load_fs(u16 selector);
void load_gs(u16 selector);

#endif