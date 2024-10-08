#include "../inc/minshell.h"

int piper(t_cmd *cmd_list, t_env_var *env_list)
{
	printf("Debug: Entering piper\n");
	int r;

	if (cmd_list == NULL)
	{
		printf("Debug: cmd_list is NULL\n");
		return 0;
	}
	r = exec_pipes(cmd_list, env_list);
	printf("Debug: Exiting piper with result %d\n", r);
	return r;
}

int init_pipes(int pipe_count, int pipefd[][2])
{
	printf("Debug: Initializing %d pipes\n", pipe_count);
	int i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipefd[i]) < 0)
		{
			printf("minishell: pipe init error\n");
			return 0;
		}
		i++;
	}
	printf("Debug: Pipes initialized successfully\n");
	return 1;
}

int exec_child_process(t_cmd *cmd_list, t_env_var *env_list, int i, int pipefd[][2])
{
	printf("Debug: Entering exec_child_process for command index %d\n", i);
	int j;
	t_cmd *current;

	current = pipe_next_index(cmd_list, i);
	printf("Debug: Current command index %d\n", current->command_index);
	if (i > 0)
		dup2(pipefd[i - 1][0], STDIN_FILENO);
	if (i < cmd_list->pipe_count)
		dup2(pipefd[i][1], STDOUT_FILENO);
	for (j = 0; j < cmd_list->pipe_count; j++)
	{
		close(pipefd[j][0]);
		close(pipefd[j][1]);
	}
	char **command = generate_command(current);
	printf("Debug: Executing command %s\n", command[0]);
	if (execve(path_finder(command[0]), command, env_list->name) == -1)
	{
		printf("minishell: execve failure\n");
		exit(EXIT_FAILURE);
	}
	return 1; // This line is technically unreachable
}

void close_pipes_in_parent(int pipe_count, int pipefd[][2], int i)
{
	printf("Debug: Closing pipes in parent for command index %d\n", i);
	if (i > 0)
		close(pipefd[i - 1][0]);
	if (i < pipe_count)
		close(pipefd[i][1]);
}

int wait_for_children(int pipe_count, pid_t pid[])
{
	printf("Debug: Waiting for %d children\n", pipe_count + 1);
	int status;
	for (int i = 0; i <= pipe_count; i++) {
		if (waitpid(pid[i], &status, 0) == -1) {
			printf("Error in waitpid\n");
			return 0;
		}
	}
	printf("Debug: All children have exited\n");
	return 1;
}

int exec_pipes(t_cmd *cmd_list, t_env_var *env_list)
{
	printf("Debug: Executing pipes for command list\n");
	int pipefd[cmd_list->pipe_count][2];
	pid_t pid[cmd_list->pipe_count + 1];
	int i;

	if (!init_pipes(cmd_list->pipe_count, pipefd))
		return 0;
	pipe_indexer(cmd_list);
	i = 0;
	while (i < cmd_list->pipe_count + 1)
	{
		printf("Debug: Forking for command index %d\n", i);
		pid[i] = fork();
		if (pid[i] == -1)
			return 0;
		if (pid[i] == 0)
			exec_child_process(cmd_list, env_list, i, pipefd);
		close_pipes_in_parent(cmd_list->pipe_count, pipefd, i);
		i++;
	}
	return wait_for_children(cmd_list->pipe_count, pid);
}

char **generate_command (t_cmd *cmd_list)
{
	char **command;
	t_cmd *current;
	int i;

	i = 0;
	current = cmd_list;
	command = malloc(sizeof(char) * 256 * 80);
	if (command == NULL)
		return NULL;
	while (current && current->type != CMD_TYPE_PIPE)
	{	
		command[i] = current->str;
		i++;
		if (current->next)
			current = current->next;
		else
			break;
	}
	return command;
}

void pipe_indexer (t_cmd *cmd_list)
{
	t_cmd *current;
	int i;

	i = 0;
	cmd_list->command_index = i;
	current = cmd_list;
	while (current)
	{
		if (current->type == CMD_TYPE_PIPE)
		{
			i++;
			if (current->next)
				current->next->command_index = i;
		}
		if (current->next)
			current = current->next;
		else
			break;
	}
}

void pipe_parsing(t_cmd *cmd_list)
{
	t_cmd *current;
	int i;

	i = 0;
	current = cmd_list;
	type_parsing(cmd_list);
	while (current)
	{
		if (current->type == CMD_TYPE_PIPE)
			i++;
		current = current->next;
	}
	cmd_list->pipe_count = i;
}

t_cmd *pipe_next_index(t_cmd *cmd_list, int index)
{
	t_cmd *current;

	current = cmd_list;
	while (current)
	{
		if (current->command_index == index)
			return current;
		if (current->next)
			current = current->next;
		else
			break;
	}
	return NULL;
}

void	type_parsing(t_cmd *cmd_list)
{
	t_cmd *current;

	current = cmd_list;
	while (current)
	{
		if (strcmp(current->str, "|") == 0)
			current->type = CMD_TYPE_PIPE;
		if (current->next)
			current = current->next;
		else
			break;
	}
}
