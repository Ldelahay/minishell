#include "../inc/minshell.h"

char *path_finder(char *fct)
{   
    char *path_env;
    char **path_dirs;
    int i;

    i = 0;
    path_env = getenv("PATH");
    if (path_env == NULL)
        return NULL;
    path_dirs = div_path(path_env);
    if (path_dirs == NULL)
        return NULL;
    while (path_dirs[i])
    {
        if (access(path_create(path_dirs[i], fct), X_OK) == 0)
            return (path_create(path_dirs[i], fct));
        i++;
    }
    return NULL;
}

char    **div_path(char *path_env)
{
    char **path_dirs;
    int i;
    int j;
    int k;

    path_dirs = malloc(sizeof(char *) * 256);
    if (path_dirs == NULL)
        return NULL;
    i = 0;
    j = 0;
    while (path_env[i])
    {
        k = 0;
        path_dirs[j] = malloc(sizeof(char) * 256);
        if (path_dirs[j] == NULL)
            return NULL;
        while (path_env[i] && path_env[i] != ':')
        {
            path_dirs[j][k] = path_env[i];
            i++;
            k++;
        }
        path_dirs[j][k] = '\0';
        j++;
        if (path_env[i] == ':')
            i++;
    }
    path_dirs[j] = NULL;
    return path_dirs;
}

char   *path_create(char *path_dir, char *fct)
{
    char *path;
    int i;
    int j;

    i = 0;
    j = 0;
    path = malloc(sizeof(char) * 256);
    if (path == NULL)
        return NULL;
    while (path_dir[i] && (my_strncmp_from_index(path_dir, fct, i) != 0))
    {
        path[j] = path_dir[i];
        i++;
        j++;
    }
    if (path[j] != '/')
    {
        path[j] = '/';
        j++;
    }
    i = 0;
    while (fct[i])
    {
        path[j] = fct[i];
        i++;
        j++;
    }
    path[j] = '\0';
    return path;
}

int my_strncmp_from_index(const char *str1, const char *str2, int i)
{
    int j;

    j = 0;
    if (i < 0 || str1[i] == '\0')
        return 0;
    while (str1[i] && str2[j]) {
        if (str1[i] != str2[j]) {
            return (unsigned char)str1[i] - (unsigned char)str2[j];
        }
        i++;
        j++;
    }
    return (0);
}