/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:48:49 by sreinhol          #+#    #+#             */
/*   Updated: 2022/03/03 22:40:47 by sreinhol         ###   ########.fr       */
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
	int		cmd_count;

	temp_c = data->cmds;
	data->actual = data->cmds;
	cmd_count = 1;
	while (temp_c->next != NULL)
	{
		if (temp_c->heredoc != -10)
			temp_c->infile = temp_c->heredoc;
		process_creator(data, temp_c, cmd_count, MIDDLE);
		temp_c = temp_c->next;
		data->actual = temp_c;
		cmd_count++;
	}
	process_creator(data, temp_c, cmd_count, LAST);
	ft_wait(data);
	free_struct(data);
}

// void	execute_cmd(t_data *data, t_cmds *temp_c, int i)
// {
// 	char	**command;
// 	char	*path;

// 	if (temp_c->builtin == true)
// 		execute_builtin(data, temp_c);
// 	else
// 	{
// 		save_paths(data);
// 		command = malloc((count_tokens(temp_c) + 1) * sizeof(char *));
// 		while (temp_c->commands[i])
// 		{
// 			command[i] = temp_c->commands[i];
// 			i++;
// 		}
// 		i = 0;
// 		if (data->dpflag == 0)
// 		{
// 			while (data->paths[i])
// 			{
// 				path = ft_strjoin(data->paths[i], "/");
// 				path = ft_strjoin(path, command[0]);
// 				if (access(path, F_OK) == SUCCESS)
// 				{
// 					if (execve(path, &command[0], data->environ) == FAILED)
// 						msg_exit(data, "execve Error\n");
// 				}
// 				i++;
// 				free(path);
// 			}
// 			free(path);
// 		}
// 		else
// 		{
// 			path = temp_c->defpath;
// 			if (access(path, F_OK) == SUCCESS)
// 			{
// 				if (execve(path, &command[0], data->environ) == FAILED)
// 					msg_exit(data, "execve Error 2\n");
// 			}
// 			free(path);
// 		}
// 		path = NULL;
// 		cmd_not_found_error(data, "Command not found\n");
// 	}
// }

static void	rec_sig_execute(int num)
{
	// printf("HELLO --------- %d\n", num);
	if (num == 2)
	{
	write(2,"hello 58\n", 10);
		write(2, "\n", 1);
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
	}
	if (num == 3)
	{
	// 		rl_on_new_line();
	// rl_redisplay();
		write(2, "Quit: 3\n", 9);
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
	}
}

void	execute_cmd(t_data *data, t_cmds *temp_c, int i)
{
	char	**command;
	char	*path;

	if (temp_c->builtin == true)
		execute_builtin(data, temp_c);
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
		cmd_not_found_error(data, "Command not found\n");
	}
}

int	is_pipe(t_cmds *temp_c)
{	
	if (temp_c->next && temp_c->next->type == PIPE)
		return (1);
	if (temp_c->prev && temp_c->prev->type == PIPE)
		return (1);
	return (0);
}

// void	exec_heredoc(t_data *data, t_cmds *temp_c)
// {
// 	int	pipe[2];

// 	ft_pipe(data, pipe);
	
// }

void	child_process(t_data *data, t_cmds *temp_c, int cmd_count, int flag)
{
	if (temp_c->infile != -5)
		ft_dup2(data, temp_c->infile, STDIN_FILENO);
	// else if (temp_c->heredoc != -10)
	// 	ft_dup2(data, temp_c->heredoc, STDIN_FILENO);
	else
		ft_dup2(data, data->save_fd, STDIN_FILENO);
	if (flag != LAST)
		ft_dup2(data, data->fd[WRITE], STDOUT_FILENO);
	else if (temp_c->outfile != -5)
		ft_dup2(data, temp_c->outfile, STDOUT_FILENO);
	ft_close(data, data->fd[READ]);
	ft_close(data, data->fd[WRITE]);
	ft_close(data, data->save_fd);
	execute_cmd(data, temp_c, 0);
	exit(g_exit);
}

void	process_creator(t_data *data, t_cmds *temp_c, int cmd_count, int flag)
{
	signal(SIGQUIT, rec_sig_execute);
	// signal(SIGINT, SIG_IGN);
	if (temp_c->builtin == true && flag == LAST && count_commands(data) == 1
		&& temp_c->exit == true)
	{
		exec_builtins(data, temp_c);
		return ;
	}
	ft_pipe(data, data->fd);
	data->pid = fork();
	if (!data->pid)
	{
		child_process(data, temp_c, cmd_count, flag);
	}
	if (data->pid)
	{
		// sleep(5);
		ft_close(data, data->fd[WRITE]);
		ft_close(data, data->save_fd);
		data->save_fd = ft_dup(data, data->fd[READ]);
		ft_close(data, data->fd[READ]);
	}
}
