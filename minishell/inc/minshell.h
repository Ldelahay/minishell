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
#include <stdbool.h> // Added for the bool type in the merged version

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"
#define MAX_TOKEN_LENGTH 256
#define MAX_TOKENS 128

typedef enum e_cmd_type
{
    CMD_TYPE_COMMAND, // Represents a command
    CMD_TYPE_ARG,     // Represents an argument to a command
    CMD_TYPE_PIPE,    // Represents a pipe ('|')
    CMD_TYPE_REDIRECT_IN,  // Represents input redirection ('<')
    CMD_TYPE_REDIRECT_OUT, // Represents output redirection ('>')
    CMD_TYPE_REDIRECT_APPEND, // Represents appending output redirection ('>>')
    CMD_TYPE_REDIRECT_IN_SYMBOL, // Represents input redirection from a symbol ('<<')
} t_cmd_type;

typedef struct s_redirection
{
    char *file; // Target file for redirection
    int fd;     // File descriptor, if needed
} t_redirection;

typedef struct s_cmd
{
	char        *str;
	int			exit_status;
	int         type;
	int         pipe_count;
	bool        is_pipe; // Added from the second version
	int         command_index; // Added from the second version
	
	struct s_cmd *prev;
	struct s_cmd *next;
} t_cmd;

//STRUCT
t_cmd *create_cmd_node(char *str);
void add_cmd_node(t_cmd **args, t_cmd *new_node);

//PARSING
int is_special_char(char c);
void ft_get_type(char *str) {}
void *ft_memset(void *ptr, int value, size_t num);

//UTILS
void ft_putstr(char *s); // Only in the first version, consider if needed
char *ft_strchr(const char *str, int search_str);
char *ft_strdup(const char *s1);
int ft_strcmp(const char *s1, const char *s2);
int ft_strlen(char *str);

//TOKENIZATION
void toker(char *line, t_cmd **cmd_list);
void handle_quote(char *line, char *token, int *j, int *i);

//EXECUTION
char    **cmd_list_to_argv(t_cmd *cmd_list);
int     execute(t_cmd *cmd_list);
int     arg_nbr(char *line) {}
int     check_delimiter(char c) {}
int     max_length(char *line) {}
int     gestion_commande(t_cmd *cmd_list);
int     exec_cl(t_cmd *cmd_list);
int     forking(t_cmd *cmd_list);
int     parent_exec(t_cmd *cmd_list);
int     need_fork(char **args);

//BUILT-INS
void    ft_echo(char **strs, int n); // Only in the first version, consider if needed

//PIPES
int     piper(t_cmd *cmd_list);
int     exec_pipes(t_cmd *cmd_list);
void    pipe_indexer(t_cmd *cmd_list); // Added from the second version
char    **generate_command(t_cmd *cmd_list); // Added from the second version
void    pipe_parsing(t_cmd *cmd_list); // Added from the second version

//PATH_FINDER
char    *path_finder(char *fct);
char    **div_path(char *path_env);
char    *path_create(char *path_dir, char *fct);
int     my_strncmp_from_index(const char *str1, const char *str2, int i);

#endif // MINISHELL_H