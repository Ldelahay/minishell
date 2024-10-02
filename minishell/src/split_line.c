#include "../inc/minshell.h"
/*
char **split_line(char *line) 
{
    int len = max_length(line);
    int i = 0;
    char **tab = malloc((arg_nbr(line) + 1) * (len * sizeof(char)));
    char *str;

    if (!tab) {
        fprintf(stderr, "allocation error\n");
        return (NULL);
    }

    // Utilisation de strtok pour découper la ligne selon les délimiteurs
    str = strtok(line, TOKEN_DELIMITERS);
    while (str != NULL) {
        tab[i] = str;
        i++;
        str = strtok(NULL, TOKEN_DELIMITERS);
    }
    tab[i] = NULL; // Marque la fin des arguments
    return tab;
}

int arg_nbr(char *line) 
{
    int i = 0;
    int j = 0;

    while (line[i]) {
        while (check_delimiter (line[i]) == 1) 
        {
            i++;
        }
        i++;
        j++;
    }
    return j;
}

int check_delimiter(char c) 
{
    int i = 0;

    while (TOKEN_DELIMITERS[i] != '\0') {
        if (TOKEN_DELIMITERS[i] == c) {
            return 1;
        }
        i++;
    }
    return 0;
}

int max_length(char *line) 
{
    int i = 0;
    int j = 0;
    int max = 0;

    while (line[i] != '\0') {
        while (check_delimiter(line[i]) == 1) {
            i++;
        }
        j = 0;
        while (check_delimiter(line[i]) == 0 && line[i] != '\0') {
            i++;
            j++;
        }
        if (j > max) {
            max = j;
        }
    }
    return max;
}
*/