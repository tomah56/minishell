/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:08:12 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/14 15:29:19 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pipes(t_data *data, int flag, t_cmds *temp_c)
{
	if (flag == FIRST && temp_c->infile != 0)
	{
		write(2, "FIRST_1\n", 8);
		data->pipefd[READ] = temp_c->infile;
	}
	if (flag == FIRST && temp_c->infile == 0)
	{
		write(2, "FIRST_2\n", 8);
		data->pipefd[READ] = STDIN_FILENO;
	}
	data->childfd[READ] = data->pipefd[READ];
	if (!(flag == LAST))
	{
		pipe(data->pipefd);
		write(2, "FIRST&MIDDLE\n", 13);
	}
	else
	{
		data->pipefd[WRITE] = temp_c->outfile;
		data->pipefd[READ] = temp_c->infile;
		write(2, "LAST\n", 5);
	}
	// data->pipefd[WRITE] = temp_c->outfile;
	data->childfd[WRITE] = data->pipefd[WRITE];
}

void	process_creator(t_data *data, t_cmds *temp_c, int flag)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILED)
		msg_exit(data, "fork process creator Error\n");
	if (pid == CHILD)
	{
		write(2, "44\n", 3);
		close(data->pipefd[READ]);
		if (dup2(data->childfd[WRITE], STDOUT_FILENO) == FAILED
			|| dup2(data->childfd[READ], STDIN_FILENO) == FAILED)
		{
			write(2, "MINI\n", 5);
			exit(EXIT_FAILURE);
		}
		close(data->childfd[WRITE]);
		close(data->childfd[READ]);
		execute_cmd(data, temp_c);
		// close(data->pipefd[WRITE]);
	}
	else
	{
		wait(0);
		write(2, "XX\n", 3);
		close(data->childfd[WRITE]);
		close(data->childfd[READ]);
	}
}

void	execute_cmd(t_data *data, t_cmds *temp_c)
{
	char	**command;
	char	*path;
	int		i;

	i = 0;
	// write(2, "35\n", 3);
	command = malloc((count_tokens(temp_c) + 1) * sizeof(char *));
	while (temp_c->commands[i])
	{
		command[i] = temp_c->commands[i];
		i++;
	}
	i = 0;
	write(2, "YO\n", 3);
	while (data->paths[i])
	{
		path = ft_strjoin(data->paths[i], "/");
		path = ft_strjoin(path, command[0]);
		if (access(path, F_OK) == SUCCESS)
		{
			write(2, "SHIT\n", 5);
			if (execve(path, &command[0], data->environ) == FAILED)
				msg_exit(data, "execve Error\n");
		}
		i++;
		free(path);
	}
	free(path);
	// ft_free_array(command);
	msg_exit(data, "Command not found\n");
}

void	ft_wait(t_data *data)
{
	pid_t	ret;
	int		wait_child;

	ret = 0;
	while (ret != -1)
	{
		ret = wait(&wait_child);
		if (ret == -1)
			break ;
		if (WIFEXITED(wait_child))
			g_exit = WEXITSTATUS(wait_child);
		// else if (WIFSIGNALED(wait_child))
		// 	wait_signal(wait_child);
	}
}

void	execute(t_data	*data)
{
	t_cmds	*temp_c;
	// char	**command;
	temp_c = data->cmds;
	// temp_c->infile = 3;
	// command = temp_c->commands;
	// printf(">>>>  %s\n", command[1]);
	// temp_c = temp_c->next;
	// printf(">>>>  %s\n", temp_c->commands[0]);
	// printf(">>>>  %s\n", temp_c->commands[1]);
	// write(2, "66\n", 3);
	pipes(data, FIRST, temp_c);
	process_creator(data, temp_c, FIRST);
	temp_c = temp_c->next;
	while (temp_c->next != NULL)
	{
		write(2, "66\n", 3);
		pipes(data, MIDDLE, temp_c);
		process_creator(data, temp_c, MIDDLE);
		temp_c = temp_c->next;
	}
	write(2, "99\n", 3);
	pipes(data, LAST, temp_c);
	process_creator(data, temp_c, LAST);
	write(2, "77\n", 3);
	ft_wait(data);
	// while (wait(NULL) != FAILED)
	// 	continue ;
	// close(data->pipefd[WRITE]);
	//free function or in main 
}
// void	execute_cmd(t_data *data, t_cmds *temp_c)
// {
// 	char	**command;
// 	char	**paths_cmd;
// 	char	*path;
// 	int		i;

// 	command = ft_split(*temp_c->commands, ' ');
// 	paths_cmd = save_paths(data,);
// 	i = 0;
// 	while (paths_cmd[i])
// 	{
// 		path = ft_strjoin(paths_cmd[i], "/");
// 		path = ft_strjoin(path, command[0]);
// 		if (access(path, F_OK) == SUCCESS)
// 		{
// 			if (execve(path, &command[0], data->environ) == FAILED)
// 				msg_exit(data, "execve Error\n");
// 		}
// 		i++;
// 		free(path);
// 	}
// 	free(path);
// 	ft_free_array(command);
// 	msg_exit(data, "Command not found\n");
// }

// void	execute(t_data	*data)
// {
// 	t_cmds	*temp_c;

// 	temp_c = data->cmds;
// 	pipes(data, FIRST, temp_c);
// 	process_creator(data, temp_c);
// 	printlist_c(temp_c);
// 	temp_c = temp_c->next;
// 	while (temp_c != NULL)
// 	{
// 		printlist_c(temp_c);
// 		pipes(data, MIDDLE, temp_c);
// 		temp_c = temp_c->next;
// 	}
// 	// printf("HELLO\n");
// 	pipes(data, LAST, temp_c);
// 	process_creator(data, temp_c);
// 	while (wait(NULL) != FAILED)
// 		continue ;
// 	//free function or in main 
// }

// void	execute_one_cmd(t_data *data)
// {
// 	int		i;
// 	char	*path;
// 	char	**command;

// 	i = 0;
// 	command = malloc((count_tokens(data->cmds) + 1) * sizeof(char *));
// 	while (data->cmds->commands[i])
// 	{
// 		command[i] = data->cmds->commands[i];
// 		i++;
// 	}
// 	i = 0;
// 	while (data->paths[i])
// 	{
// 		path = ft_strjoin(data->paths[i], "/");
// 		path = ft_strjoin(path, command[0]);
// 		if (access(path, F_OK) == 0)
// 		{
// 			if (execve(path, &command[0], data->environ) == FAILED)
// 				msg_exit(data, "execve error");
// 		}
// 		i++;
// 		free(path);
// 	}
// 	write(2, "Command not found\n", 18);
// 	free(path);
// }

//function that checks for builtins