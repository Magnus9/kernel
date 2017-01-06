
#include <vga.h>
#include <idt.h>

int kmain(void *multiboot_hdr)
{
    vga_init();
    idt_init();

    return 0;
}