#include "../inc/minshell.h"

static int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

void handle_quote(char *line, char *token, int *j, int *i)
{
    char quote_type = line[*i];
    (*i)++; // Move past the opening quote

    if (line[*i] == quote_type)
        (*i)++;
    while (line[*i] != '\0')
    {
        if (line[*i] == quote_type)
        {
            // If we find the closing quote, move past it and return
            (*i)++;
            return;
        }
        else if (*j < MAX_TOKEN_LENGTH - 1)
        {
            // Add characters inside the quotes to the token
            token[(*j)++] = line[*i];
        }
        (*i)++;
    }
    token[*j] = '\0';
}

void toker(char *line, t_cmd **cmd_list)
{
    if (line == NULL || cmd_list == NULL || !line[0])
    {
        printf("command list or line null\n");
        return;
    }
    char token[MAX_TOKEN_LENGTH] = {0};
    int i;
    int j;

    i = 0;
    j = 0; 

    while (line[i] != '\0')
    {
        memset(token, 0, MAX_TOKEN_LENGTH);
        while (line[i] && ft_isspace(line[i]))
            i++;
        while (line[i] && !ft_isspace(line[i]))
        {
            if (line[i] == '"' || line[i] == '\'')
                handle_quote(line, token, &j, &i);
            else if(!ft_isspace(line[i]))
                token[j++] = line[i];
            if (line[i] != '\0')
                i++;
            else break;
        }
        if (j > 0) // If we have collected a token
        {
            t_cmd *new_node = create_cmd_node(token);
            add_cmd_node(cmd_list, new_node);
        }
        j = 0;
    }
}

/*
The Valgrind output indicates that the issue is not 
directly related to the tokenization process
shown in the provided code snippet. 
Instead, the problem lies in the 
`path_create` and `path_finder` functions, 
as mentioned in the Valgrind output. 
The error `Conditional jump or move depends on 
uninitialized value(s)` suggests that these 
functions are using variables that have not been 
initialized before their use.
*/