#include "../../inc/minshell.h"

int builtin_check(char **args)
{
    int i;
    int n_flag;
    char **echo_args;

    i = 0;
    n_flag = 0;
    if (!args || !args[i])
    {
        printf("invalid args/n");
        return 0;
    }
    if (ft_strcmp(args[i], "exit") == 0)
        ft_exit(1);
    else if (ft_strcmp(args[i],"cd") == 0)
    {
        change_dir(args);
        return 1;
    }
    else if (ft_strcmp(args[i],"echo") == 0)
    {
        echo_args = &args[i + 1];
        if (ft_strcmp(echo_args[0], "-n") == 0)
        {
            n_flag = 1;
            echo_args = &args[i + 2];
        }
        ft_echo(echo_args, n_flag);
        return 1;
    }
    else if (ft_strcmp(args[i], "pwd") == 0)
    {
        ft_pwd();
        return 1;
    }
    else if (ft_strcmp(args[i],"env") == 0)
    {
        ft_env(environ);
        return 1;
    }
    return (0);
}
