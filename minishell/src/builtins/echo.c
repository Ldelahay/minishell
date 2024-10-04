#include "../inc/minshell.h"

static int ft_strslen(char **strs)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    len = 0;
    if (!strs || !*strs)
        return (0);
    while (strs[i])
    {
        while (strs[i][j])
        {
            j++;
            len++;
        }
        j = 0;
        i++;
    }
    return (len);
}
static char *ft_cat_res(char **strs, char *res, int n)
{
    int i;
    int j;
    int k;

    i = 0;
    k = 0;
    while(strs[i])
    {
        j = 0;
        while(strs[i][j])
            res[k++] = strs[i][j++];
        i++;
    }
    if (n == 1)
        res[k] = '\0';
    else
    {
        res[k] = '\n';
        res[k + 1] = '\0';
    }
    return (res);
}
void    ft_echo(char **strs, int n)
{
    int i;
    int j;
    int len;
    char *res;

    i = 0;
    j = 0;
    if (!strs[i] || ! strs[i][j])
        return ;
    len = ft_strslen(strs);
    if (n == 1)
        res = malloc(sizeof(char) * (len + 1));
    else
        res = malloc(sizeof(char) * (len + 2));
    if (!res)
        return ;
    ft_cat_res(strs, res, n);
    ft_putstr(res);
    free(res);
}