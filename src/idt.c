
#include <idt.h>

static struct idt_descriptor idt_table[256]
    __attribute__ ((aligned(8)));

void idt_init(void)
{
    struct idt_base base = {
        sizeof(idt_table) - 1,
        (u32)idt_table
    };
    lidt(&base);
}

void idt_init_descriptor(struct idt_descriptor *desc,
                         u32 base)
{
    desc->off_low = base & 0xffff;
    desc->selector = 0x08;
    desc->zero = 0;
    desc->attr = IDT_INTERRUPT_MASK | IDT_DPL0;
    desc->off_high = base & 0xffff0000;
}

void lidt(void *base)
{
    __asm__ __volatile__ ("lidt %0" : : "m" (base));
}

void sidt(struct idt_base *base)
{
    __asm__ __volatile__ ("sidt %0" : "=m" (base));
}