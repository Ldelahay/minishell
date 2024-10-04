#include "../inc/minshell.h"


int piper(t_cmd *cmd_list)
{
	int r;

	if (cmd_list == NULL)
		return 0;
	r = exec_pipes(cmd_list);
	printf("piper 2\n");
	return r;
}

int exec_pipes(t_cmd *cmd_list)
{
	int pipefd[cmd_list->pipe_count * 2];
	t_cmd *current;
	pid_t pid;
	int i;
	int j;

	i = 0;
	j = 0;
	current = cmd_list;
	while (i < cmd_list->pipe_count)
	{
		if (pipe(pipefd + i * 2) < 0)
		{
			perror("pipe");
			return 0;
		}
		i++;
	}
	i = 0;
	pipe_indexer (cmd_list);
	printf("exec_pipes 2\n");
	while (i < cmd_list->pipe_count + 1)
	{
		pid = fork();
		if (pid == -1)
			return 0;
		while (current->command_index != i)
		{
			printf("current->command_index : %d\n", current->command_index);
			current = current->next;
		}
		if (pid == 0)
		{
			if (current->command_index > 0)
				dup2(pipefd[(i - 1) * 2], STDIN_FILENO);
			if (i == cmd_list->pipe_count)
				dup2(pipefd[(i * 2) + 1], STDOUT_FILENO);
			while (j < cmd_list->pipe_count * 2)
			{
				close(pipefd[j]);
				j++;
			}
			execve(path_finder(generate_command(current)[0]), generate_command(current), NULL);
		}
		printf("i : %d\n", i);
		i++;
	}
	printf("exec_pipes 3\n");
	return 1;
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
	while (current && current->is_pipe == false)
	{
		while (current->str[i])
		{
			command[i] = current->str;
			i++;
		}
		i++;
	}
	return command;
}

void pipe_indexer (t_cmd *cmd_list)
{
	t_cmd *current;
	int i;

	i = cmd_list->pipe_count;
	printf("i : %d\n", i);
	cmd_list->command_index = i;
	current = cmd_list;
	while (current)
	{
		if (current->is_pipe == true)
		{
			i--;
			if (current->next)
				current->next->command_index = i;
		}
		printf("i \n");
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
	while (current)
	{
		if (strcmp(current->str, "|") == 0)
		{
			current->is_pipe = true;
			i++;
		}
		current = current->next;
	}
	cmd_list->pipe_count = i;
}