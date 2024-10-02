#include "../inc/minshell.h"

int main(int argc, char **argv) {
    char *line;
    char **args;
    int status;

    line = NULL;
    args = NULL;
    status = 1;
    (void)argc;
    (void)argv;
    while (status)
    {
        line = readline("minishell@localhost:~$ ");
        args = split_line(line);
        status = execute(args);

        free(line);
        free(args);
    }
    return 0;
}