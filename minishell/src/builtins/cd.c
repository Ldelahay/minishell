#include "../../inc/minshell.h"

int change_dir(char **args)
{
    char *path;

    if (args == NULL || strcmp(args[0], "cd") != 0)
        return -1; // Invalid command list or not a "cd" command
    if (args[1] == NULL || strcmp(args[1], "~") == 0)
    {
        path = getenv("HOME");
        if (path == NULL)
        {
            printf("minishell: HOME not set\n");
            return -2; // Indicate missing HOME environment variable
        }
    }
    else 
    {
        path = args[1];
    }
    chdir(path);
    return 1; // Success
}
