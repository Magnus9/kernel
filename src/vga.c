
#include <vga.h>
#include <string.h>

static u32 x, y = 0;

void clear_screen(void)
{
    u32 i;

    for (i = 0; i < (COLS * ROWS); i++)
        printchar(' ');
    x = 0;
    y = 0;
}

void scroll_rows(void)
{
    u16 ch, *addr = (u16 *)VGA_TEXT_BASE;

    for (y = 0; y < ROWS - 1; y++) {
        for (x = 0; x < COLS; x++) {
            ch = *(addr + ((y + 1) * COLS + x));
            *(addr + (y * COLS + x)) = ch;
        }
    }
    x = 0;
}

void printchar(u8 ch)
{
    u16 *addr = (u16 *)VGA_TEXT_BASE;

    if (x >= COLS) {
        x = 0;
        y += 1;
    }
    if (y >= ROWS) {
        scroll_rows();
    }
    switch(ch) {
        case '\n':
            x = 0;
            y += 1;
        break;
        case '\r':
            x = 0;
        break;
        default:
            *(addr + (y * COLS + x++)) = ch | TEXT_COLOR << 8;
        break;
    }
}

void printstr(const char *str)
{
    char *p;

    for (p = str; *p != '\0'; p++)
        printchar(*p);
}

void printf(char *str, ...)
{
    char **params = (char **)&str;
    char buf[40], *param;
    u32 i, j;

    for (i = 0; i < strlen(str); i++) {
        if (str[i] != '%')
            printchar(str[i]);
        else {
            switch(str[++i]) {
                case 's':
                    param = *++params;
                case 'd':
                    param = gen_base_string(buf, 10, *(u32 *)++params);
                break;
                case 'x':
                    param = gen_base_string(buf, 16, *(u32 *)++params);
                break;
                default:
                    printchar(*(char *)++params);
                    continue;
                break;
            }
            for (j = 0; j < strlen(param); j++)
                printchar(param[j]);
        }
    }
}

char *gen_base_string(char *buf, u32 base, u32 num)
{
    char *p = buf;
    char *p1, *p2, tmp;
    u32 rem;

    if (num < 0) {
        *p++ = '-';
        buf++;
        num = -num;
    }
    do {
        rem = num % base;
        *p++ = (rem < 10) ? rem + '0' : rem + 'a' - 10;
    } while (num /= base);
    *p = '\0';

    for (p1 = buf, p2 = p - 1; p1 < p2;
         p1++, p2--) {
        tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
    }
    return buf;
}

int vga_init(void)
{
    clear_screen();

    return 0;
}