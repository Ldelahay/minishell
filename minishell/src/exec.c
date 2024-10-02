#include "../inc/minshell.h"

int execute(char **args) {
    if (gestion_commande(args) == 0)
            return 0;
    return 1;
}

int gestion_commande(char **args)
{
    if (need_fork(args) == 1)
        return (forking(args));
    else 
        return (parent_exec(args));
    return 1;
}

int forking(char **args)
{
    int status;
    pid_t pid;
    int ret;
    int i;

    i = 0;
    pid = fork();
    while (args[i])
    {
        if (strcmp(args[i], "exit") == 0)
            return 0;
        i++;
    }
    if (pid == 0)
    {
        ret = exec_cl(args);
        if (ret == -1) {
            printf("minishell: command not found\n");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
            printf("minishell: fork failed\n");
    } else {
        waitpid(pid, &status, WUNTRACED);
    }
    return 1;
}

int parent_exec(char **args)
{
    if (strcmp(args[0], "cd") == 0)
    {
        if (args[1] == NULL)
            printf("minishell: expected argument to \"cd\"\n");
        else if (chdir(args[1]) != 0)
            printf("repertoire introuvable\n");
        return 1;
    }
    return 1;
}