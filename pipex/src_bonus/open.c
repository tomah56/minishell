/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 15:35:31 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/12 15:32:23 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

// checks if process is first, middle or last
void	pipes(t_pipex *pipex, int flag, char **argv, int argc)
{
	if ((flag == FIRST) && !pipex->heredoc)
		pipex->pipefd[READ] = open(argv[1], O_RDONLY);
	if (pipex->pipefd[READ] == FAILED)
		perror(argv[1]);
	pipex->childfd[READ] = pipex->pipefd[READ];
	if (!(flag == LAST))
	{
		if (pipe(pipex->pipefd) == FAILED)
			error("pipe");
	}
	else
	{
		if (pipex->heredoc)
			pipex->pipefd[WRITE] = open(argv[argc - 1], O_WRONLY
					| O_CREAT | O_APPEND, 0644);
		else
			pipex->pipefd[WRITE] = open(argv[argc - 1], O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		pipex->pipefd[READ] = STDIN_FILENO;
		if (pipex->pipefd[WRITE] == FAILED)
			error(argv[argc - 2]);
	}
	pipex->childfd[WRITE] = pipex->pipefd[WRITE];
}



void	pipes_2(t_data *data, int flag, t_cmds *temp_c)
{
	if (flag == FIRST)
		data->pipefd[READ] = temp_c->infile;
	data->childfd[READ] = data->pipefd[READ];
	if (flag == MIDDLE || flag == FIRST)
	{
		pipe(data->pipefd);
	}
	if (flag == MIDDLE || flag == LAST)
	{
		write(2, "PO\n", 3);
		data->pipefd[WRITE] = STDOUT_FILENO;
		data->pipefd[READ] = data->childfd[WRITE];
	}
	data->childfd[WRITE] = data->pipefd[WRITE];
}