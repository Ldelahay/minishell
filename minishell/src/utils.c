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
void ft_memdel(void **ap)
{
    if (ap && *ap)
    {
        free(*ap); // Free the allocated memory
        *ap = NULL; // Set the pointer to NULL to avoid dangling pointer issues
    }
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

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    while (n && *s1 && (*s1 == *s2)) {
        s1++;
        s2++;
        n--;
    }
    if (n == 0) {
        return 0;
    } else {
        return (*(unsigned char *)s1 - *(unsigned char *)s2);
    }
}
