#include "../inc/minshell.h"

void init_tokenizer(char ***tokens, char *token, int *token_count)
{
    *tokens = malloc(sizeof(char *) * MAX_TOKENS);
    memset(token, 0, MAX_TOKEN_LENGTH);
    *token_count = 0;
}

void add_token(char ***tokens, char *token, int *token_count)
{
    if (ft_strlen(token) > 0)
    {
        (*tokens)[*token_count] = ft_strdup(token);
        (*token_count)++;
        memset(token, 0, MAX_TOKEN_LENGTH);
    }
}

void handle_special_char(char ***tokens, char *token, int *token_count, char c)
{
    add_token(tokens, token, token_count);
    token[0] = c;
    add_token(tokens, token, token_count);
}

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

char **toker(char *line)
{
    int token_count;
    char **tokens;
    char token[MAX_TOKEN_LENGTH] = {0};
    init_tokenizer(&tokens, token, &token_count);
    int i = 0;
    int j = 0;

    while (line[i])
    {
        // Ignorer les espaces
        while (line[i] && ft_isspace(line[i]))
            i++;
        
        // Traiter les caractères non espacés
        while (line[i] && !ft_isspace(line[i]))
        {
            if (line[i] == '"' || line[i] == '\'')
                handle_quote(line, token, &j, &i); // Passer i par référence
            else if (is_special_char(line[i]))
            {
                handle_special_char(&tokens, token, &token_count, line[i]);
                j = 0; // Réinitialiser j après un caractère spécial
            }
            else 
            {
                token[j++] = line[i];
                i++;
            }
        }
        printf("token: %s\n", token);
        add_token(&tokens, token, &token_count);
        memset(token, 0, MAX_TOKEN_LENGTH);
        j = 0;  // Réinitialiser j après avoir ajouté un token
    }
    printf("token_count: %d\n", token_count);

    // Allouer l'espace pour le dernier NULL
    tokens = realloc(tokens, sizeof(char *) * (token_count + 1));
    tokens[token_count] = NULL;

    return tokens;
}
