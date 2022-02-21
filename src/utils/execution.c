/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:48:49 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/21 17:19:14 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		else if (ret == data->pid)
		{
			if (WIFEXITED(wait_child))
				g_exit = WEXITSTATUS(wait_child);
		}
	}
}

void	execute(t_data *data)
{
	t_cmds	*temp_c;

	temp_c = data->cmds;
	data->actual = data->cmds;
	while (temp_c->next != NULL)
	{
		if (temp_c->heredoc != -10)
			temp_c->infile = temp_c->heredoc;
		process_creator(data, temp_c, MIDDLE);
		temp_c = temp_c->next;
		data->actual = temp_c;
	}
	process_creator(data, temp_c, LAST);
	ft_wait(data);
	free_struct(data);
}

void	close_fds(t_data *data, t_cmds *temp_c, int fd[2])
{
	if (dup2(fd[READ], data->save_fd) == FAILED)
		dup_exit(data, "2dup error ");
	close(fd[WRITE]);
	close(fd[READ]);
	if (temp_c->infile != STDIN_FILENO)
		close(temp_c->infile);
	if (temp_c->outfile != STDOUT_FILENO)
		close(temp_c->outfile);
	close(STDOUT_FILENO);
	if (dup2(data->fdout, STDOUT_FILENO) == FAILED)
		dup_exit(data, "4dup error ");
	if (temp_c->next == NULL)
	{
		if (data->save_fd != STDIN_FILENO)
			close(data->save_fd);
	}
}

void	execute_cmd(t_data *data, t_cmds *temp_c, int i)
{
	char	**command;
	char	*path;

	if (temp_c->builtin == true)
	{
		execute_builtin(data, temp_c);
		close(temp_c->infile);
		close(temp_c->outfile);
		exit(g_exit);
	}
	else
	{
		save_paths(data);
		command = malloc((count_tokens(temp_c) + 1) * sizeof(char *));
		while (temp_c->commands[i])
		{
			command[i] = temp_c->commands[i];
			i++;
		}
		i = 0;
		while (data->paths[i])
		{
			path = ft_strjoin(data->paths[i], "/");
			path = ft_strjoin(path, command[0]);
			if (access(path, F_OK) == SUCCESS)
			{
				if (execve(path, &command[0], data->environ) == FAILED)
					msg_exit(data, "execve Error\n");
			}
			i++;
			free(path);
		}
		path = NULL;
		msg_exit(data, "Command not found\n");
	}
}

void	process_creator(t_data *data, t_cmds *temp_c, int flag)
{
	int	fd[2];

	if (temp_c->infile != STDIN_FILENO)
	{
		if (dup2(temp_c->infile, data->save_fd) == FAILED)
			dup_exit(data, "5dup error ");
	}
	if (temp_c->builtin == true && flag == LAST && data->tokencount == 1)
	{
		execute_builtin(data, temp_c);
		return ;
	}
	if (pipe(fd) == FAILED)
		msg_exit(data, "pipe error\n");
	data->pid = fork();
	if (data->pid == FAILED)
		msg_exit(data, "fork error\n");
	if (data->pid == CHILD)
	{
		close(fd[READ]);
		if (dup2(data->save_fd, STDIN_FILENO) == FAILED)
			dup_exit(data, "6dup error ");
		if (flag == LAST)
		{
			if (dup2(temp_c->outfile, STDOUT_FILENO) == FAILED)
				dup_exit(data, "7dup error ");
			close(fd[WRITE]);
		}
		else
		{
			if (dup2(fd[WRITE], STDOUT_FILENO) == FAILED)
				dup_exit(data, "8dup error ");
		}
		execute_cmd(data, temp_c, 0);
		exit(g_exit);
	}
	close(fd[WRITE]);
	close(fd[READ]);
	if (temp_c->next == NULL)
	{
		if (data->save_fd != STDIN_FILENO)
			close(data->save_fd);
	}
}
