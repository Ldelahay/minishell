#include "../inc/minshell.h"

static void free_cmds(t_cmd *cmd_list) {
	t_cmd *current_node = cmd_list;
	t_cmd *next_node;

	while (current_node != NULL) {
		next_node = current_node->next; // Save reference to the next node
		free(current_node->str); // Assuming each node has a dynamically allocated string 'str'
		free(current_node); // Free the current node
		current_node = next_node; // Move to the next node
	}
}

int main(int argc, char **argv) {
	char *line;
	t_cmd **cmd_list;
	int status;

	line = NULL;
	status = 1;
	(void)argc;
	(void)argv;

	cmd_list = malloc(sizeof(t_cmd*));
	if (cmd_list == NULL) {
		perror("Failed to allocate memory for cmd_list");
		return 1; // Exit if memory allocation fails
	}
	*cmd_list = NULL; // Ensure the list is initially empty

	while (status)
	{
		line = readline("minishell@localhost:~$ ");
		if (line && *line)
			add_history(line);
		toker(line, cmd_list);
/*		if (cmd_list && *cmd_list)
		{
			printf("Arguments:\n");
		for (current_node = *cmd_list; current_node != NULL; current_node = current_node->next)
			printf("%s\n", current_node->str); // Print each command/argument
		}*/
		status = execute(*cmd_list);
		free(line);
		free_cmds(*cmd_list);
		*cmd_list = NULL;
	}
	free(cmd_list);
	return 0;
}