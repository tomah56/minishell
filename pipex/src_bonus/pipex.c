/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:41:13 by sreinhol          #+#    #+#             */
/*   Updated: 2021/12/27 12:33:27 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

// finds path in envp and saves it in struct
void	save_path(t_pipex *pipex, char **envp)
{
	while (*envp != NULL && ft_strncmp(*envp, "PATH=", 5))
		++envp;
	if (*envp == NULL)
		error("PATH not found\n");
	pipex->path_envp = (*envp + 5);
	pipex->paths_cmd = ft_split(pipex->path_envp, ':');
	if (!pipex->paths_cmd)
		free_paths(pipex);
}

// checks for invalid nbr of input and calls heredoc function
void	input_check(int argc, char **argv, t_pipex *pipex)
{
	if (argc < 5)
		error_msg("Invalid number of arguments\n");
	pipex->heredoc = !ft_strncmp(argv[1], "here_doc", 9);
	if (pipex->heredoc && argc < 6)
		error_msg("Invalid number of arguments\n");
	if (pipex->heredoc == 1)
		pipex->pipefd[READ] = here_doc(argv[2]);
	pipes(pipex, FIRST, argv, argc);
}

void	execute_cmd(t_pipex *pipex, char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**command;

	i = 0;
	command = ft_split(cmd, ' ');
	while (pipex->paths_cmd[i])
	{
		path = ft_strjoin(pipex->paths_cmd[i], "/");
		path = ft_strjoin(path, command[0]);
		if (access(path, F_OK) == 0)
		{
			if (execve(path, &command[0], envp) == FAILED)
				error("execve Error\n");
		}
		i++;
		free(path);
	}
	free(path);
	ft_free_array(command);
	error("Command not found");
}

void	process_creator(t_pipex *pipex, char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILED)
		error("fork process creator Error\n");
	if (pid == CHILD)
	{
		close(pipex->pipefd[READ]);
		if (dup2(pipex->childfd[WRITE], STDOUT_FILENO) == FAILED
			|| dup2(pipex->childfd[READ], STDIN_FILENO) == FAILED)
			exit(EXIT_FAILURE);
		close(pipex->childfd[WRITE]);
		close(pipex->childfd[READ]);
		execute_cmd(pipex, cmd, envp);
	}
	else
	{
		close(pipex->childfd[WRITE]);
		close(pipex->childfd[READ]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	save_path(&pipex, envp);
	input_check(argc, argv, &pipex);
	i = 2 + pipex.heredoc;
	process_creator(&pipex, argv[i], envp);
	i++;
	while (i < argc - 2)
	{
		pipes(&pipex, MIDDLE, argv, argc);
		process_creator(&pipex, argv[i], envp);
		i++;
	}
	pipes(&pipex, LAST, argv, argc);
	process_creator(&pipex, argv[i], envp);
	while (wait(NULL) != FAILED)
		continue ;
	ft_free_array(pipex.paths_cmd);
	return (0);
}
