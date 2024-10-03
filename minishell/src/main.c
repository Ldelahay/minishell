#include "../inc/minshell.h"

int main(int argc, char **argv) {
    char *line;
    char **args;
    int status;
    int i;

    line = NULL;
    args = NULL;
    status = 1;
    (void)argc;
    (void)argv;

    while (status)
    {
        line = readline("minishell@localhost:~$ ");
        if (line && *line)
            add_history(line);
        args = toker(line);
        if (args) {
            printf("Arguments:\n");
            for (i = 0; args[i] != NULL; i++) {
                printf("arg[%d]: %s\n", i, args[i]);
            }
        }
        status = execute(args);
        free(line);
        free(args);
    }
    return 0;
}