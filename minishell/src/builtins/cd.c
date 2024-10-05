#include "../../inc/minshell.h"

int change_dir(t_cmd *cmd_list)
{
    if (cmd_list == NULL || strcmp(cmd_list->str, "cd") != 0)
        return -1; // Invalid command list or not a "cd" command

    t_cmd *arg = cmd_list->next; // The argument to "cd"
    if (arg == NULL || arg->str == NULL)
    {
        printf("minishell: expected argument to \"cd\"\n");
        return 1; // Indicate missing argument error
    }
    if (chdir(arg->str) != 0)
    {
        perror("minishell: cd error"); // Use perror to print the error related to chdir
        return 2; // Indicate chdir failure
    }
    return 0; // Success
}
