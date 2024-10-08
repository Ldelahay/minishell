#include "../../inc/minshell.h"
/*
char *get_env_name(char *dest, const char *src)
{
    int i;

    i = 0;
    while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

int is_already_env(t_env_var *env_list, char *args)
{
    char var_name[BUFF_SIZE];
    char env_name[BUFF_SIZE];

    get_env_name(var_name, args);
    while (env_list && env_list->next)
    {
        if (ft_strcmp(var_name, env_name) == 0)
        {
            ft_memdel(env_list->value);
            env_list->value = ft_strdup(args);
            return (1);
        }
        env_list = env_list->next;
    }
    return (1);
}

int ft_export(char **args, t_env_var *env_list)
{
    int error_val;

    if(!args[1]) // NO ARG
    {
        //PRINT ENV LIST
        return (1);
    }
    if (args[1][0] == '=') //special case starts with = invalid
        error_val = -1;
    if (error_val <= 0)
        return (print_error(error_val, args[1])); //PRINT ERROR
    if (error_val == 2 || !is_already_env(env_list, args[1]))
    {
        if (error_val == 1) //new env var
            env_add(args[1], env_list);
    }
    return (1);
}
*/