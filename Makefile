
SRCDIR  = src
INCLDIR = include

CFLAGS  = -I$(INCLDIR) -m32 -nostdlib
LDFLAGS = -T linker.ld -melf_i386
OBJECTS = bootstrap.o main.o string.o vga.o gdt.o idt.o

kernel: $(OBJECTS)
	ld $(LDFLAGS) -o $@ $(OBJECTS)
	mv kernel /mnt/boot/
	sync

bootstrap.o: $(SRCDIR)/bootstrap.S
	cc -c $(CFLAGS) -o $@ $(SRCDIR)/bootstrap.S

string.o: $(SRCDIR)/string.c $(INCLDIR)/string.h
	cc -c $(CFLAGS) -o $@ $(SRCDIR)/string.c

vga.o: $(SRCDIR)/vga.c $(INCLDIR)/vga.h
	cc -c $(CFLAGS) -o $@ $(SRCDIR)/vga.c

gdt.o: $(SRCDIR)/gdt.c $(INCLDIR)/gdt.h
	cc -c $(CFLAGS) -o $@ $(SRCDIR)/gdt.c

idt.o: $(SRCDIR)/idt.c $(INCLDIR)/idt.h
	cc -c $(CFLAGS) -o $@ $(SRCDIR)/idt.c

main.o: $(SRCDIR)/main.c
	cc -c $(CFLAGS) -o $@ $(SRCDIR)/main.c

clean:
	rm *.o