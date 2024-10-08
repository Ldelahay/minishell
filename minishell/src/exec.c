#include "../inc/minshell.h"


static void print_cmd_list(t_cmd *cmd_list) {
    t_cmd *current = cmd_list;
    while (current != NULL) {
        if (current->str != NULL) {
            //printf("Command: %s\n", current->str);
        } else {
            //printf("Command is NULL\n");
        }
        current = current->next;
    }
}

static void print_cmd_types(t_cmd *cmd_list) {
    while (cmd_list != NULL) {
        switch (cmd_list->type) {
            case CMD_TYPE_PIPE:
                //printf("CMD_TYPE_PIPE\n");
                break;
            case CMD_TYPE_REDIRECT_IN:
                //printf("CMD_TYPE_REDIRECT_IN\n");
                break;
            case CMD_TYPE_REDIRECT_OUT:
                //printf("CMD_TYPE_REDIRECT_OUT\n");
                break;
            case CMD_TYPE_REDIRECT_APPEND:
                //printf("CMD_TYPE_REDIRECT_APPEND\n");
                break;
            case CMD_TYPE_REDIRECT_IN_SYMBOL:
                //printf("CMD_TYPE_REDIRECT_IN_SYMBOL\n");
                break;
            case CMD_TYPE_COMMAND:
                //printf("CMD_TYPE_COMMAND\n");
                break;
            case CMD_TYPE_ARG:
                //printf("CMD_TYPE_ARG\n");
                break;
            default:
                //printf("Unknown Command Type\n");
        }
        cmd_list = cmd_list->next;
    }
}

int execute(t_cmd *cmd_list, t_env_var *env_list)
{ // CHECK FOR BUILTINS HERE
    if (cmd_list == NULL)
        return -1;
    if (gestion_commande(cmd_list, env_list) == 0)
        return 0;
    return 1;
}

int gestion_commande(t_cmd *cmd_list, t_env_var *env_list)
{
    print_cmd_list(cmd_list);
    print_cmd_types(cmd_list);
    handle_redirections(cmd_list);
    if (builtin_check(cmd_list_to_argv(cmd_list)) == 1)
        return (1);
    if (cmd_list->pipe_count > 0)
        return (piper(cmd_list, env_list));
    else if (need_fork(cmd_list_to_argv(cmd_list)) == 1)
        return (forking(cmd_list, env_list));
    return (1);
}
int forking(t_cmd *cmd_list, t_env_var *env_list)
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
        ret = exec_cl(cmd_list, env_list);
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