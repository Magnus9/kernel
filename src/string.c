
#include <types.h>

u32 strlen(const char *str)
{
    int num = 0;
    char *p;

    for (p = str; *p != '\0'; p++)
        num++;

    return num;
}

char *strncpy(char *dst, const char *src,
              u32 len)
{
    int i;

    for (i = 0; i < len; i++)
        dst[i] = src[i];

    return dst;
}