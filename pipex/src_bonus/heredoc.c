/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 15:33:41 by sreinhol          #+#    #+#             */
/*   Updated: 2021/12/27 01:45:36 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	here_doc_helper(char *limiter, int *fd)
{
	char	*read;
	char	*limiter_nl;

	close(fd[READ]);
	limiter_nl = ft_strjoin(limiter, "\n");
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		read = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(read, limiter_nl, ft_strlen(limiter) + 1))
			break ;
		write(fd[WRITE], read, ft_strlen(read));
		ft_free(read);
	}
	ft_free(read);
	close(fd[WRITE]);
	exit(EXIT_SUCCESS);
}

int	here_doc(char *limiter)
{
	int		pid;
	int		fd[2];

	if (pipe(fd) == FAILED)
		error("pipe Error\n");
	pid = fork();
	if (pid == FAILED)
		error("fork heredoc Error\n");
	if (pid == CHILD)
		here_doc_helper(limiter, fd);
	else
	{
		close(fd[WRITE]);
		waitpid(pid, NULL, 0);
	}
	return (fd[READ]);
}
