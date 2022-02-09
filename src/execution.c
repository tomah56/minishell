/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:08:12 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/09 22:04:39 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pipes(t_data *data, int flag, t_cmds *temp_c)
{
	data->pipefd[READ] = temp_c->infile;
	if (data->pipefd[READ] == FAILED)
	{
		write(2, "ERROR\n", 6); // temporarly
		return (-1);
	}
	data->childfd[READ] = data->pipefd[READ];
	if (!(flag == LAST))
	{
		if (pipe(data->pipefd) == FAILED)
		{
			write(2, "ERROR\n", 6); // temporarly
			return (-1);
		}
	}
	else
	{
		data->pipefd[WRITE] = temp_c->outfile;
		if (data->pipefd[WRITE] == FAILED)
		{
			write(2, "ERROR\n", 6); // temporarly
			return (-1);
		}
	}
	data->childfd[WRITE] = data->pipefd[WRITE];
}

void	execute(t_data	*data)
{
	t_cmds	*temp_c;

	temp_c = data->cmds;
	if (temp_c->infile == FAILED || temp_c->outfile == FAILED)
		return (NULL);
	// for the first cmd
	// do we have handeled the input redirection?
	pipes(data, FIRST, temp_c);
}


//we probably need a flag for heredoc
//function that checks for builtins