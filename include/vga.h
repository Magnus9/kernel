
#ifndef INCLUDE_VGA_H
#define INCLUDE_VGA_H

#include <types.h>

#define VGA_TEXT_BASE   0xb8000
#define COLS            80
#define ROWS            25

enum {
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_RED,
    COLOR_MAGENTA,
    COLOR_BROWN,
    COLOR_LIGHTGRAY,
    COLOR_DARK_GRAY,
    COLOR_LIGHT_BLUE,
    COLOR_LIGHT_GREEN,
    COLOR_LIGHT_CYAN,
    COLOR_LIGHT_RED,
    COLOR_LIGHT_MAGENTA,
    COLOR_YELLOW,
    COLOR_WHITE
};
#define TEXT_COLOR      COLOR_WHITE

void clear_screen(void);
void scroll_rows(void);
void printchar(u8 ch);
void printstr(const char *str);
void printf(char *str, ...);
char *gen_base_string(char *buf, u32 base, u32 num);
int vga_init(void);

#endif