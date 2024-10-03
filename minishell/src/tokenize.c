#include "../inc/minshell.h"

static int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

void handle_quote(char *line, char *token, int *j, int *i)
{
    char quote_type = line[*i];  // Utiliser *i pour accéder au caractère actuel
    (*i)++;  // Avancer après le guillemet ouvrant

    // Ajouter les caractères entre les guillemets
    while (line[*i] != quote_type && line[*i] != '\0')
    {
        token[(*j)++] = line[*i];
        (*i)++;
    }

    // Si on rencontre le guillemet fermant, avancer d'un pas
    if (line[*i] == quote_type)
        (*i)++;
}

void toker(char *line, t_cmd **cmd_list)
{
    if (line == NULL || cmd_list == NULL)
    {
        printf("command list or line null\n");
        return;
    }
    char token[MAX_TOKEN_LENGTH] = {0};
    int i;
    int j;

    i = 0;
    j = 0; 

    while (line[i])
    {
        memset(token, 0, MAX_TOKEN_LENGTH);
        while (line[i] && ft_isspace(line[i]))
            i++;
        while (line[i] && !ft_isspace(line[i]))
        {
            if (line[i] == '"' || line[i] == '\'')
                handle_quote(line, token, &j, &i);
            else
                token[j++] = line[i++];
        }
        if (j > 0) // If we have collected a token
        {
            t_cmd *new_node = create_cmd_node(token);
            add_cmd_node(cmd_list, new_node);
        }
        j = 0;
    }
}
