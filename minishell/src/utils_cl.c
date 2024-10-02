#include "../inc/minshell.h"

extern char **environ;

int need_fork(char **args)
{
    if (strcmp(args[0], "cd") == 0)
        return 0;
    return 1;
}

char *path_finder(char **args)
{
    if (strcmp(args[0], "ls") == 0)
        return "/bin/ls";
    if (strcmp(args[0], "pwd") == 0)
        return "/bin/pwd";
    if (strcmp(args[0], "cat") == 0)
        return "/bin/cat";
    if (strcmp(args[0], "echo") == 0)
        return "/bin/echo";
    if (strcmp(args[0], "touch") == 0)
        return "/bin/touch";
    if (strcmp(args[0], "mkdir") == 0)
        return "/bin/mkdir";
    if (strcmp(args[0], "rm") == 0)
        return "/bin/rm";
    if (strcmp(args[0], "rmdir") == 0)
        return "/bin/rmdir";
    if (strcmp(args[0], "clear") == 0)
        return "/bin/clear";
    return NULL;
}

int exec_cl(char **args)
{
    int r;

    r = execve(path_finder(args), args, environ);
    return r;
}
