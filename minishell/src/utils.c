#include "../inc/minshell.h"

void ft_putstr(char *s)
{
    if (s)
    {
        while (*s)
        {
            write(1, s++, 1);
        }
    }
}
int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

void *my_calloc(size_t num, size_t size)
{
    size_t totalSize = num * size;
    void *ptr = malloc(totalSize);
    if (ptr != NULL) {
        ft_memset(ptr, 0, totalSize);
    }
    return ptr;
}
