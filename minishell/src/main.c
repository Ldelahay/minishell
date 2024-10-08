#include "../inc/minshell.h"

static void free_cmds(t_cmd *cmd_list)
{
	t_cmd *current_node = cmd_list;
	t_cmd *next_node;

	while (current_node != NULL) {
		next_node = current_node->next; // Save reference to the next node
		free(current_node->str); // Assuming each node has a dynamically allocated string 'str'
		free(current_node); // Free the current node
		current_node = next_node; // Move to the next node
	}
}

static void minishell(t_cmd **cmd_list, t_env_var *env_list)
{
	int status;
	char *line;

	line = NULL;
	status = 1;
	while (status)
	{
		line = readline("minishell@localhost:~$ ");
		if (line == NULL)
		{
			printf("\nExit\n");
			break ;
		}
		if (line && *line)
			add_history(line);
		toker(line, cmd_list);
		get_cmd_types(*cmd_list);
		pipe_parsing(*cmd_list); // Use pipe_parsing from the second main
		status = execute(*cmd_list, env_list);
		free(line);
		free_cmds(*cmd_list);
		*cmd_list = NULL;
	}
}
static void sigint_handler(int sig_num)
{
    (void)sig_num;
    printf("\nminishell@localhost:~$ ");
    fflush(stdout);
}

static void sigquit_handler(int sig_num)
{
    (void)sig_num;
    printf("\nQuit (core dumped)\n");
    exit(0);
}

int main(int argc, char **argv)
{
	t_cmd **cmd_list;
	t_env_var *env_list;
	char *original_term;

	original_term = getenv("TERM");
	env_list = malloc(sizeof(t_env_var));
	init_env(env_list);
	(void)argc;
	(void)argv;

	signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);

	cmd_list = malloc(sizeof(t_cmd*));
	if (cmd_list == NULL) {
		perror("Failed to allocate memory for cmd_list");
		return 1; // Exit if memory allocation fails
	}
	*cmd_list = NULL; // Ensure the list is initially empty
	unset_env(env_list, "TERM");
	set_env(env_list, "TERM", "vt100");
	minishell(cmd_list, env_list);
	if (original_term)
	{
		unset_env(env_list, "TERM");
		set_env(env_list, "TERM", original_term);
	}
	free(cmd_list);
	return 0;
}
