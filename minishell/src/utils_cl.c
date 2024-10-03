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
// Helper function to convert t_cmd list to char**
char **cmd_list_to_argv(t_cmd *cmd_list)
{
    int count = 0;
    t_cmd *current = cmd_list;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    char **argv = malloc((count + 1) * sizeof(char *));
    if (argv == NULL) {
        return NULL;
    }

    current = cmd_list;
    for (int i = 0; i < count; i++) {
        argv[i] = current->str;
        current = current->next;
    }
    argv[count] = NULL;

    return argv;
}

int exec_cl(t_cmd *cmd_list)
{
    char **args = cmd_list_to_argv(cmd_list);
    if (args == NULL) {
        return -1;
    }

    int r = execve(path_finder(args), args, environ);
    free(args);
    return r;
}
