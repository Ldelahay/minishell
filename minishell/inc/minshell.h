#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>


#define TOKEN_BUFSIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"
#define MAX_TOKEN_LENGTH 256
#define MAX_TOKENS 128


//PARSING

char *ft_strchr(const char *str, int search_str);
char *ft_strdup(const char *s1);
int ft_strlen(char *str);
int is_special_char(char c);
void *ft_memset(void *ptr, int value, size_t num);

//TOKENIZATION

char **toker(char *line);
void add_token(char ***tokens, char *token, int *token_count);
void handle_quote(char **line, char *token, int *j);
void handle_special_char(char ***tokens, char *token, int *token_count, char c);
void init_tokenizer(char ***tokens, char *token, int *token_count);

//LUCA'S SHIT
int     execute(char **args);
char    **split_line(char *line);
int     arg_nbr(char *line);
int     check_delimiter(char c);
int     max_length(char *line);
int     gestion_commande(char **args);
int     exec_cl(char **args);
char    *path_finder(char **args);
int     forking(char **args);
int     parent_exec(char **args);
int     need_fork(char **args);



#endif 