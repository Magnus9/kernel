
#include <vga.h>
#include <gdt.h>
#include <idt.h>

int kmain(void *multiboot_hdr)
{
    vga_init();
    gdt_init();
    idt_init();

    int n = 1 / 0;

    return 0;
}