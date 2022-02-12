/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:08:12 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/12 14:24:56 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	pipes(t_data *data, int flag, t_cmds *temp_c)
// {
// 	if (flag == FIRST)
// 		data->pipefd[READ] = temp_c->infile;
// 	data->childfd[READ] = data->pipefd[READ];
// 	data->childfd[READ] = data->pipefd[READ];
// 	if (flag == MIDDLE || flag == FIRST)
// 	{
// 		write(2, "NO\n", 3);
// 		pipe(data->pipefd);
// 	}
// 	else
// 		data->pipefd[WRITE] = temp_c->outfile;
// 	data->childfd[WRITE] = data->pipefd[WRITE];
// }

// void	process_creator(t_data *data, t_cmds *temp_c)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == FAILED)
// 		msg_exit(data, "fork process creator Error\n");
// 	if (pid == CHILD)
// 	{
// 		close(data->pipefd[READ]);
// 		if (dup2(data->childfd[WRITE], temp_c->outfile) == FAILED
// 			|| dup2(data->childfd[READ], temp_c->infile) == FAILED)
// 			exit(EXIT_FAILURE);
// 		close(data->childfd[WRITE]);
// 		close(data->childfd[READ]);
// 		execute_cmd(data, temp_c);
// 	}
// 	else
// 	{
// 		close(data->childfd[WRITE]);
// 		close(data->childfd[READ]);
// 	}
// }

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