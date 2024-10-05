#include "../inc/minshell.h"

int execute(t_cmd *cmd_list)
{
    if (gestion_commande(cmd_list) == 0)
        return 0;
    return 1;
}

int gestion_commande(t_cmd *cmd_list)
{
    if (cmd_list->pipe_count > 0)
        return (piper(cmd_list));
    else if (need_fork(cmd_list_to_argv(cmd_list)) == 1)
        return (forking(cmd_list));
    else
        return (change_dir(cmd_list)); // in cd.c need to fix cd closing program
}

int forking(t_cmd *cmd_list)
{
    int status;
    pid_t pid;
    int ret;
    t_cmd *current;

    current = cmd_list;
    if (current == NULL)
        return -1;
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
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else if (pid < 0)
    {
        printf("minishell: fork failed\n");
        return -2;
    }
    else 
    {
        waitpid(pid, &status, WUNTRACED);
        return 1;
    }
}