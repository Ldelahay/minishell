#include "../inc/minshell.h"

char *ft_strchr(const char *str, int search_str)
{
    while (*str != '\0')
    {
        if (*str == (char)search_str)
            return (char *)str;
        str++;
    }
    if (search_str == '\0')
        return (char *)str;
    return (NULL);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

void *ft_memset(void *ptr, int value, size_t num)
{
    unsigned char *p;
    p = ptr;
    while (num--)
    {
        *p++ = (unsigned char)value;
    }
    return ptr;
}

char *ft_strdup(const char *s1)
{
    size_t len;
    size_t i;
    char *res;

    len = 0;
    if(!s1)
        return NULL ;
    while(s1[len])
        len++;
    res = malloc(len + 1);
    if (!res)
        return NULL;
    i = 0;
    while (i < len)
    {
        res[i] = s1[i];
        i++;
    }
    res[i] = '\0';
    return res;
}
int is_special_char(char c)
{
    return strchr("|&><", c) != NULL;
}