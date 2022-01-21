/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 22:04:05 by sreinhol          #+#    #+#             */
/*   Updated: 2021/12/26 22:19:08 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	error_msg(char *error)
{
	write(2, error, ft_strlen(error));
	return (EXIT_FAILURE);
}

void	error(char *error)
{
	perror(error);
	exit (EXIT_FAILURE);
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipe[READ]);
	close(pipex->pipe[WRITE]);
}

void	check_init_error(t_pipex *pipex)
{
	if (!pipex->cmd1)
	{
		free_cmd1(pipex);
		perror("Error - init command 1");
	}
	if (!pipex->cmd2)
	{
		free_cmd2(pipex);
		perror("Error - init command 2");
	}
	if (!pipex->paths)
	{
		free_paths(pipex);
		error("Error - init paths");
	}
}
