/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:27:23 by sreinhol          #+#    #+#             */
/*   Updated: 2021/12/27 14:33:44 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_1_process(t_pipex *pipex, char **envp)
{
	if (dup2(pipex->pipe[WRITE], STDOUT_FILENO) == FAILED)
		return (error("error dup2\n"));
	close(pipex->pipe[READ]);
	if (dup2(pipex->fdin, STDIN_FILENO) == FAILED)
		return (error("error dup2\n"));
	execve(pipex->path1, &pipex->cmd1[0], envp);
	if (execve(pipex->path1, &pipex->cmd1[0], envp) == FAILED)
		error("execve Error\n");
}

void	child_2_process(t_pipex *pipex, char **envp)
{
	if (dup2(pipex->pipe[READ], STDIN_FILENO) == FAILED)
		return (error("error dub2\n"));
	close(pipex->pipe[WRITE]);
	if (dup2(pipex->fdout, STDOUT_FILENO) == FAILED)
		return (error("error dup2\n"));
	execve(pipex->path2, &pipex->cmd2[0], envp);
	if (execve(pipex->path2, &pipex->cmd2[0], envp) == FAILED)
		error("execve Error\n");
}
