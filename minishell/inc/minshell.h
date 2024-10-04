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

typedef struct s_cmd
{
	char        *str;
	int         type;
	int 	   	pipe_count;
	bool		is_pipe;
	
	struct s_cmd *prev;
	struct s_cmd *next;
} t_cmd;

//STRUCT
t_cmd *create_cmd_node(char *str);
void add_cmd_node(t_cmd **args, t_cmd *new_node);

//PARSING

char *ft_strchr(const char *str, int search_str);
char *ft_strdup(const char *s1);
int ft_strlen(char *str);
int is_special_char(char c);
void ft_get_type(char *str);
void *ft_memset(void *ptr, int value, size_t num);

//TOKENIZATION

void toker(char *line, t_cmd **cmd_list);
void handle_quote(char *line, char *token, int *j, int *i);

//EXECUTION
char    **cmd_list_to_argv(t_cmd *cmd_list);
int     execute(t_cmd *cmd_list);
int     arg_nbr(char *line);
int     check_delimiter(char c);
int     max_length(char *line);
int     gestion_commande(t_cmd *cmd_list);
int     exec_cl(t_cmd *cmd_list);
int     forking(t_cmd *cmd_list);
int     parent_exec(t_cmd *cmd_list);
int     need_fork(char **args);

//PATH_FINDER

char	*path_finder(char *fct);
char	**div_path(char *path_env);
char	*path_create(char *path_dir, char *fct);
int		my_strncmp_from_index(const char *str1, const char *str2, int i);



#endif 