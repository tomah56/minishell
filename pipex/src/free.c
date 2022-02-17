/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:29:08 by sreinhol          #+#    #+#             */
/*   Updated: 2021/12/23 22:36:33 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_cmd1(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd1[i])
	{
		free(pipex->cmd1[i]);
		i++;
	}
	free(pipex->cmd1[i]);
	free(pipex->cmd1);
}

void	free_cmd2(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd2[i])
	{
		free(pipex->cmd2[i]);
		i++;
	}
	free(pipex->cmd2[i]);
	free(pipex->cmd2);
}

void	free_paths(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->fdin);
	close(pipex->fdout);
	while (pipex->paths[i])
	{
		free(pipex->paths[i]);
		i++;
	}
	free(pipex->paths[i]);
	free(pipex->path2);
	free(pipex->path1);
}

void	free_struct(t_pipex *pipex)
{
	ft_free_array(pipex->paths);
	ft_free_array(pipex->cmd1);
	ft_free_array(pipex->cmd2);
	free(pipex->path1);
	pipex->path1 = NULL;
	free(pipex->path2);
	pipex->path2 = NULL;
}
