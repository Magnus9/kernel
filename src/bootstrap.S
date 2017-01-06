
#define MULTIBOOT_HEADER_MAGIC      0x1badb002
#define MULTIBOOT_HEADER_FLAGS      0x00000003
#define STACK_SIZE                  0x4000

.section .text
    .globl start
    start:
        jmp multiboot_entry

        .align 4
        multiboot_header:
            .long MULTIBOOT_HEADER_MAGIC
            .long MULTIBOOT_HEADER_FLAGS
            .long -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

        multiboot_entry:
            movl $(stack + STACK_SIZE), %esp

        pushl %ebx

        jmp kmain

        loop:
            hlt
            jmp loop

.section .bss
    .comm stack, STACK_SIZE
