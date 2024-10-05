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
