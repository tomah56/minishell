/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:48:49 by sreinhol          #+#    #+#             */
/*   Updated: 2022/03/06 16:47:40 by sreinhol         ###   ########.fr       */
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

static void	rec_sig_execute(int num)
{
	if (num == 2)
	{
		write(2, "\n", 1);
	}
	if (num == 3)
	{
		write(2, "Quit: 3\n", 9);
	}
}

void	child_process(t_data *data, t_cmds *temp_c, int cmd_count, int flag)
{
	if (temp_c->fail == 1)
		exit(g_exit);
	if (temp_c->infile != -5)
		ft_dup2(data, temp_c->infile, STDIN_FILENO);
	else
		ft_dup2(data, data->save_fd, STDIN_FILENO);
	if (temp_c->outfile != -5)
		ft_dup2(data, temp_c->outfile, STDOUT_FILENO);
	else if (flag != LAST || (temp_c->last == false && flag == LAST))
		ft_dup2(data, data->fd[WRITE], STDOUT_FILENO);
	ft_close(data, data->fd[READ]);
	ft_close(data, data->fd[WRITE]);
	ft_close(data, data->save_fd);
	execute_cmd(data, temp_c, 0);
	exit(g_exit);
}

void	process_creator(t_data *data, t_cmds *temp_c, int cmd_count, int flag)
{
	signal(SIGQUIT, rec_sig_execute);
	signal(SIGINT, rec_sig_execute);
	if (temp_c->builtin == true && flag == LAST && count_commands(data) == 1
		&& temp_c->type == 0)
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
		ft_close(data, data->fd[WRITE]);
		ft_close(data, data->save_fd);
		data->save_fd = ft_dup(data, data->fd[READ]);
		ft_close(data, data->fd[READ]);
	}
}
