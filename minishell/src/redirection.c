#include "../inc/minshell.h"

static int handle_redirect_in(t_cmd *cmd)
{
    int fd = open(cmd->str, O_RDONLY);
    if (fd == -1) return (-1);
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        close(fd); // Ensure the file descriptor is closed on error
        return (-1);
    }
    close(fd);
    return (1);
}

static int handle_redirect_out(t_cmd *cmd)
{
    printf("%s\n", cmd->str);
    int fd = open(cmd->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return (-1);
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        close(fd);
        return (-1);
    }
    close(fd);
    return (1);
}
static int handle_redirect_append(t_cmd *cmd)
{
    int fd = open(cmd->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) return (-1);
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        close(fd);
        return (-1);
    }
    close(fd);
    return (1);
}

int handle_redirections(t_cmd *cmd_list)
{
    t_cmd *current;

    while (cmd_list)
    {
        if (cmd_list->type == CMD_TYPE_COMMAND)
        {
            current = cmd_list->next;
            while (current && (current->type == CMD_TYPE_REDIRECT_IN || current->type == CMD_TYPE_REDIRECT_OUT || current->type == CMD_TYPE_REDIRECT_APPEND || current->type == CMD_TYPE_REDIRECT_IN_SYMBOL))
            {
                if (!current->next)
                    return (-1);
                if (current->type == CMD_TYPE_REDIRECT_IN)
                {
                    if (handle_redirect_in(current->next) == -1) return (-1);
                }
                else if (current->type == CMD_TYPE_REDIRECT_OUT)
                {
                    if (handle_redirect_out(current->next) == -1) return (-1);
                }
                else if (current->type == CMD_TYPE_REDIRECT_APPEND)
                {
                    if (handle_redirect_append(current->next) == -1) return (-1);
                }
                current = current->next;
            }
        }
        cmd_list = cmd_list->next;
    }
    return (1);
}
