#include "../inc/minshell.h"

/*
void get_cmd_types(t_cmd *cmd_list)
{
    while (cmd_list->next)
    {
        if ft_strcmp()
    }
} */

t_cmd *create_cmd_node(char *str)
{
    t_cmd *new_node = malloc(sizeof(t_cmd));
    if (!new_node)
        return NULL;
    new_node->str = ft_strdup(str);
    if (!new_node->str)
    {
        free(new_node);
        return NULL;
    }
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->command_index = 0;
    return new_node;
}
void add_cmd_node(t_cmd **args, t_cmd *new_node)
{
    t_cmd *tmp;

    if (!new_node)
        return;
    if (!*args)
    {
        *args = new_node;
        return;
    }
    tmp = *args;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
    new_node->prev = tmp;
}
