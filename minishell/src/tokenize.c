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

void handle_quote(char **line, char *token, int *j)
{
    char quote_type = **line;
    (*line)++;
    while (**line != quote_type && **line != '\0')
    {
        token[(*j)++] = **line;
        (*line)++;
    }
    if (**line == quote_type)
        (*line)++;
}
char **toker(char *line)
{
    int token_count;
    char **tokens;
    char token[MAX_TOKEN_LENGTH] = {0};
    init_tokenizer(&tokens, token, &token_count);

    for (int i = 0, j = 0; line[i] != '\0'; i++)
    {
        if (line[i] == '"' || line[i] == '\'')
            handle_quote(&line, token, &j);
        else if (is_special_char(line[i]))
        {
            handle_special_char(&tokens, token, &token_count, line[i]);
            j = 0;
        }
        else 
        {
            token[j++] = line[i];
        }
    }
    add_token(&tokens, token, &token_count);
    tokens = realloc(tokens, sizeof(char*) * (token_count + 1));
    tokens[token_count] = NULL;
    return tokens;
}
