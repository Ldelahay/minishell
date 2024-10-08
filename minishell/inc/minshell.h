#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h> // Added for the bool type in the merged version

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"
#define MAX_TOKEN_LENGTH 256
#define MAX_TOKENS 128
#define BUFF_SIZE 4096

extern char **environ;

typedef struct s_env_var
{
	char **name;
} t_env_var;

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
	int         command_index; // Added from the second version
	
	struct s_cmd *prev;
	struct s_cmd *next;
} t_cmd;

//STRUCT
t_cmd *create_cmd_node(char *str);
void add_cmd_node(t_cmd **args, t_cmd *new_node);

//PARSING
int is_special_char(char c);
void get_cmd_types(t_cmd *cmd_list);
void *ft_memset(void *ptr, int value, size_t num);

//UTILS
void ft_putstr(char *s); // Only in the first version, consider if needed
char *ft_strchr(const char *str, int search_str);
void ft_memdel(void **ap);
char *ft_strdup(const char *s1);
void *my_calloc(size_t num, size_t size);
int ft_strcmp(const char *s1, const char *s2);
int ft_strlen(char *str);
int ft_strncmp(const char *s1, const char *s2, size_t n);

//TOKENIZATION
void toker(char *line, t_cmd **cmd_list);
void handle_quote(char *line, char *token, int *j, int *i);

//EXECUTION
char    **cmd_list_to_argv(t_cmd *cmd_list);
int     execute(t_cmd *cmd_list, t_env_var *env_list);
int     arg_nbr(char *line) ;
int     check_delimiter(char c);
int     max_length(char *line);
int     gestion_commande(t_cmd *cmd_list, t_env_var *env_list);
int     exec_cl(t_cmd *cmd_list, t_env_var *env_list);
int     forking(t_cmd *cmd_list, t_env_var *env_list);
int     need_fork(char **args);

//BUILT-INS
int     builtin_check(char **args);
void    ft_env(char **env);
void    ft_echo(char **strs, int n); // Only in the first version, consider if needed
int     change_dir(char **args);
int     ft_pwd(void);
void    ft_exit(int status);

//REDIRECTIONS
int handle_redirections(t_cmd *cmd_list);

//PIPES
int     piper(t_cmd *cmd_list, t_env_var *env_list);
int     exec_pipes(t_cmd *cmd_list, t_env_var *env_list);
void    pipe_indexer(t_cmd *cmd_list);
char    **generate_command(t_cmd *cmd_list);
void    pipe_parsing(t_cmd *cmd_list);
t_cmd   *pipe_next_index(t_cmd *cmd_list, int index);
t_cmd   *last_pipe(t_cmd *cmd_list);
void    type_parsing(t_cmd *cmd_list);

//PATH_FINDER
char    *path_finder(char *fct);
char    **div_path(char *path_env);
char    *path_create(char *path_dir, char *fct);
int     my_strncmp_from_index(const char *str1, const char *str2, int i);

//ENV
void    init_env(t_env_var *env_list);
void    unset_env(t_env_var *env_list, const char *var);
void    set_env(t_env_var *env_list, const char *var, const char *value);

#endif // MINISHELL_H