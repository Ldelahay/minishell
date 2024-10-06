#include "../../inc/minshell.h"

int ft_pwd(void)
{
    char *cwd;
    cwd = (char *)malloc(PATH_MAX * sizeof(char));
    if (cwd == NULL)
    {
        printf("minishell:malloc error\n");
        return -1;
    }
    if (getcwd(cwd, PATH_MAX) == NULL)
    {
        printf("minishell:cwd error\n");
        free(cwd);
        return -1;
    }
    printf("%s\n", cwd);
    free(cwd);
    return 1;
}
