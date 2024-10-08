#include "../inc/minshell.h"

int need_fork(char **args)
{
    if (args[0] == NULL || strcmp(args[0], "cd") == 0)
        return 0;
    return 1;
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

int exec_cl(t_cmd *cmd_list, t_env_var *env_list)
{
    char *path;
    char **args = cmd_list_to_argv(cmd_list);
    if (cmd_list == NULL)
        return -1;
    if (args == NULL)
        return -1;
    path = path_finder(args[0]);
    if (path == NULL)
        return -1;
    int r = execve(path, args, env_list->name);
    if (r == -1)
        perror("execve error");
    if (path != NULL)
        free (path);
    return r;
}
