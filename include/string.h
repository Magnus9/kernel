
#ifndef INCLUDE_STRING_H
#define INCLUDE_STRING_H

#include <types.h>

u32 strlen(const char *str);
char *strncpy(char *dst, const char *src,
              u32 len);
#endif