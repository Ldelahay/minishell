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