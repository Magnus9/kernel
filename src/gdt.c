
#include <gdt.h>

static struct gdt_descriptor gdt_table[GDT_TABLE_SIZE]
    __attribute__ ((aligned(8)));

void gdt_init(void)
{
    struct gdt_base base = {
        sizeof(gdt_table) - 1,
        (u32)gdt_table
    };
    /*
     * Initialize a flat model for now
     */
    // Null.
    gdt_init_descriptor(&gdt_table[GDT_NULL], 0, 0, 0, 0);
    // Kernel code.
    gdt_init_descriptor(&gdt_table[GDT_KERN_CODE], 0, 0xfffff,
                        GDT_PRESENT | GDT_DPL0 | GDT_CODE_DATA | GDT_EXEC |
                        GDT_PRIVILEGE, GDT_GRAN | GDT_PROT_MODE);
    // Kernel data.
    gdt_init_descriptor(&gdt_table[GDT_KERN_DATA], 0, 0xfffff,
                        GDT_PRESENT | GDT_DPL0 | GDT_CODE_DATA | GDT_PRIVILEGE,
                        GDT_GRAN | GDT_PROT_MODE);
    // User code.
    gdt_init_descriptor(&gdt_table[GDT_USER_CODE], 0, 0xfffff,
                        GDT_PRESENT | GDT_DPL3 | GDT_CODE_DATA | GDT_EXEC |
                        GDT_PRIVILEGE, GDT_GRAN | GDT_PROT_MODE);
    // User data.
    gdt_init_descriptor(&gdt_table[GDT_USER_DATA], 0, 0xfffff,
                        GDT_PRESENT | GDT_DPL3 | GDT_CODE_DATA | GDT_PRIVILEGE,
                        GDT_GRAN | GDT_PROT_MODE);
    lgdt(&base);
    load_cs();
    load_ss(GDT_KERN_DATA << 3);
    load_ds(GDT_KERN_DATA << 3);
    load_es(GDT_KERN_DATA << 3);
    load_fs(GDT_KERN_DATA << 3);
    load_gs(GDT_KERN_DATA << 3);
}

void gdt_init_descriptor(struct gdt_descriptor *desc,
                         u32 base, u32 limit, u8 access,
                         u8 flags)
{
    desc->limit_low = limit & 0xffff;
    desc->base_low = base & 0xffff;
    desc->base_med = base >> 16;
    desc->access = access;
    desc->flags_limit_high = flags & 0xf0 | (limit >> 16) & 0x0f;
    desc->base_high = base >> 24;
}

void lgdt(struct gdt_base *base)
{
    __asm__ __volatile__ ("lgdt %0" : : "m" (*base));
}

void sgdt(struct gdt_base *base)
{
    __asm__ __volatile__ ("sgdt %0" : "=m" (*base));
}

void load_cs(void)
{
    __asm__ __volatile__ ("jmp %0, $label" : : "i" (GDT_KERN_CODE << 3));
    __asm__ __volatile__ ("label:");
}

void load_ss(u16 selector)
{
    __asm__ __volatile__ ("movw %w0, %%ss" : : "r" (selector));
}

void load_ds(u16 selector)
{
    __asm__ __volatile__ ("movw %w0, %%ds" : : "r" (selector));
}

void load_es(u16 selector)
{
    __asm__ __volatile__ ("movw %w0, %%es" : : "r" (selector));
}

void load_fs(u16 selector)
{
    __asm__ __volatile__ ("movw %w0, %%fs" : : "r" (selector));
}

void load_gs(u16 selector)
{
    __asm__ __volatile__ ("movw %w0, %%gs" : : "r" (selector));
}