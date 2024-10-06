#include "../../inc/minshell.h"

extern char **environ;

void ft_env(char **env)
{
    if (*env == NULL)
        return;
    printf("%s\n", *env);
    ft_env(env + 1);
}
