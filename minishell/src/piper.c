#include "../inc/minshell.h"

int piper(t_cmd *cmd_list, t_env_var *env_list)
{
	int r;

	if (cmd_list == NULL)
		return 0;
	r = exec_pipes(cmd_list, env_list);
	return r;
}

int exec_pipes(t_cmd *cmd_list, t_env_var *env_list)
{
	int pipefd[cmd_list->pipe_count][2];
	t_cmd *current;
	pid_t pid[cmd_list->pipe_count + 1];
	int i;
	int j;
	int status;

	i = 0;
	j = 0;
	current = cmd_list;
	type_parsing(cmd_list);
	while (i < cmd_list->pipe_count)
	{
		if (pipe(pipefd[i]) < 0)
		{
			perror("pipe");
			return 0;
		}
		i++;
	}
	i = 0;
	pipe_indexer (cmd_list);
	while (i < cmd_list->pipe_count + 1)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return 0;
		if (pid[i] == 0)
		{
			current = pipe_next_index(current, i);
			if (i > 0)
				dup2(pipefd[i - 1][0], STDIN_FILENO);
			if (i < cmd_list->pipe_count) {
    			dup2(pipefd[i][1], STDOUT_FILENO);
			}
			while (j < cmd_list->pipe_count)
			{
				close(pipefd[j][0]);
				close(pipefd[j][1]);
				j++;
			}
			if (execve(path_finder(generate_command(current)[0]), generate_command(current), env_list->name) == -1)
			{
				printf("erreur execve\n");
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
		j = 0;
		if (i > 0)
			close(pipefd[i - 1][0]);
    	if (i < cmd_list->pipe_count) 
		{
			close(pipefd[i][1]);
		}
		i++;
	}
	if (waitpid(pid[i], &status, 0) == -1)
	{
		printf("erreur waitpid\n");
		return 0;
	}
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
