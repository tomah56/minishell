/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 22:04:05 by sreinhol          #+#    #+#             */
/*   Updated: 2021/12/27 00:55:27 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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

void	free_paths(t_pipex *pipex)
{
	ft_free_array(pipex->paths_cmd);
	free(pipex->path_envp);
	error_msg("ENVP Error\n");
	exit(1);
}
