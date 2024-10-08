#include "../inc/minshell.h"

extern char **environ;

void print_env(t_env_var *env_list) {
    int i = 0;
    while (env_list->name[i] != NULL) {
        printf("%s\n", env_list->name[i]);
        i++;
    }
}

void set_env(t_env_var *env_list, const char *var, const char *value) {
    int i;
    int len = ft_strlen((char *)var);
    char *new_var = malloc(len + ft_strlen((char *)value) + 2); // +2 pour '=' et '\0'
    if (!new_var) {
        printf("Failed to allocate memory for new environment variable");
        return;
    }
    i = 0;
    while (i < len) {
        new_var[i] = var[i];
        i++;
    }
    new_var[len] = '=';
    i = 0;
    while (value[i] != '\0') {
        new_var[len + 1 + i] = value[i];
        i++;
    }
    new_var[len + 1 + i] = '\0';
    i = 0;
    while (env_list->name[i] != NULL) {
        if (ft_strncmp(env_list->name[i], var, len) == 0 && env_list->name[i][len] == '=') {
            free(env_list->name[i]);
            env_list->name[i] = new_var;
            return;
        }
        i++;
    }
    env_list->name = realloc(env_list->name, sizeof(char *) * (i + 2));
    if (!env_list->name) {
        printf("Failed to reallocate memory for environment variables");
        free(new_var);
        return;
    }
    env_list->name[i] = new_var;
    env_list->name[i + 1] = NULL;
}

void unset_env(t_env_var *env_list, const char *var) {
    int i;
    int j;
    size_t len = strlen(var);

    i = 0;
    while (env_list->name[i] != NULL) {
        if (ft_strncmp(env_list->name[i], var, len) == 0 && env_list->name[i][len] == '=') {
            free(env_list->name[i]);
            j = i;
            while (env_list->name[j] != NULL) {
                env_list->name[j] = env_list->name[j + 1];
                j++;
            }
            return;
        }
        i++;
    }
}

void init_env(t_env_var *env_list) {
    int i = 0;
    int count = 0;

    while (environ[count] != NULL) {
        count++;
    }
    env_list->name = malloc(sizeof(char *) * (count + 1));
    if (!env_list->name) {
        printf("Failed to allocate memory for environment variables");
        return;
    }
    while (environ[i] != NULL) {
        env_list->name[i] = ft_strdup(environ[i]);
        if (!env_list->name[i]) {
            printf("Failed to allocate memory for environment variable");
            while (i > 0) {
                free(env_list->name[--i]);
            }
            free(env_list->name);
            return;
        }
        i++;
    }
    env_list->name[i] = NULL;
}