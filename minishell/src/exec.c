#include "../inc/minshell.h"

int execute(t_cmd *cmd_list)
{
    if (gestion_commande(cmd_list) == 0)
        return 0;
    return 1;
}

int gestion_commande(t_cmd *cmd_list)
{
    if (need_fork(cmd_list_to_argv(cmd_list)) == 1)
        return (forking(cmd_list));
    //else if (cmd_list->pipe_count > 0)
    //    return (piper(cmd_list));
    else 
        return (parent_exec(cmd_list));
    return 1;
}

int forking(t_cmd *cmd_list)
{
    int status;
    pid_t pid;
    int ret;
    t_cmd *current;

    current = cmd_list;
    if (current == NULL)
        return 1;
    while (current)
    {
        if (current->str != NULL && strcmp(current->str, "exit") == 0)
            return 0;
        current = current->next;
    }
    pid = fork();
    if (pid == 0)
    {
        ret = exec_cl(cmd_list);
        if (ret == -1) {
            printf("minishell: command not found\n");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        printf("minishell: fork failed\n");
        return -1;
    }
    else 
        waitpid(pid, &status, WUNTRACED);
    return 1;
}

int parent_exec(t_cmd *cmd_list)
{
    if (cmd_list == NULL)
        return 1; // No command to execute

    // Assuming the first command is the actual command and the second is its argument
    if (strcmp(cmd_list->str, "cd") == 0)
    {
        t_cmd *arg = cmd_list->next; // The argument to "cd"
        if (arg == NULL || arg->str == NULL)
            printf("minishell: expected argument to \"cd\"\n");
        else if (chdir(arg->str) != 0)
            printf("repertoire introuvable\n");
        return 1;
    }
    return 1;
}