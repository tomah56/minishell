/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 15:35:31 by sreinhol          #+#    #+#             */
/*   Updated: 2021/12/27 12:38:41 by sreinhol         ###   ########.fr       */
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
