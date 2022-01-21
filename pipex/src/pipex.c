/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:41:13 by sreinhol          #+#    #+#             */
/*   Updated: 2021/12/27 18:36:57 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// finds path in envp and saves it in struct
void	save_path(char **argv, t_pipex *pipex, char **envp)
{
	char	*path_envp;

	while (*envp != NULL && ft_strncmp(*envp, "PATH=", 5))
		++envp;
	if (*envp == NULL)
		error("PATH not found\n");
	while (envp)
	{
		path_envp = ft_substr(*envp, 5, strlen(*envp) - 5);
		if (ft_strncmp(*envp, "PATH=", 5) == SUCCESS)
		{
			pipex->paths = ft_split(path_envp, ':');
			if (pipex->paths == NULL)
				return ;
			break ;
		}
		free(path_envp);
		++envp;
	}
	free(path_envp);
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	check_init_error(pipex);
}

// finds the correct path for command 1, print error if not found
static void	get_path_1(t_pipex *pipex)
{
	char	*temp;
	int		i;

	i = 0;
	while (pipex->paths[i])
	{
		temp = ft_strjoin(pipex->paths[i], "/");
		pipex->path1 = ft_strjoin(temp, *pipex->cmd1);
		free(temp);
		if (access(pipex->path1, F_OK) == SUCCESS)
			return ;
		i++;
		free(pipex->path1);
	}
	ft_putstr_fd("Command 1 not found\n", 2);
	exit(127);
}

// finds the correct path for command 2, print error if not found
static void	get_path_2(t_pipex *pipex)
{
	char	*temp;
	int		i;

	i = 0;
	while (pipex->paths[i])
	{
		temp = ft_strjoin(pipex->paths[i], "/");
		pipex->path2 = ft_strjoin(temp, *pipex->cmd2);
		free(temp);
		if (access(pipex->path2, F_OK) == 0)
			return ;
		i++;
		free(pipex->path2);
	}
	ft_putstr_fd("Command 2 not found\n", 2);
	exit(127);
}

// checks for invalid nbr of input and opens files
void	input_check(int argc, char **argv, t_pipex *pipex)
{
	if (argc != 5)
		error_msg("Invalid number of arguments\n");
	pipex->fdin = open(argv[1], O_RDONLY);
	if (pipex->fdin < 0)
		error_msg("open Error\n");
	pipex->fdout = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (pipex->fdout < 0)
		error_msg("open Error\n");
	if (pipe(pipex->pipe) == FAILED)
		error("pipe Error\n");
	if (argc == 5)
	{
		if (pipex->fdin == FAILED || pipex->fdout == FAILED)
			error("open Error\n");
	}
	if (access(argv[1], F_OK) != SUCCESS)
		error("File 1 not found");
}

int	main(int argc, char **argv, char **envp)
{
	static t_pipex	pipex;
	pid_t			child_1;
	pid_t			child_2;

	input_check(argc, argv, &pipex);
	save_path(argv, &pipex, envp);
	get_path_1(&pipex);
	get_path_2(&pipex);
	child_1 = fork();
	if (child_1 == CHILD)
		child_1_process(&pipex, envp);
	child_2 = fork();
	if (child_2 == CHILD)
		child_2_process(&pipex, envp);
	close_pipes(&pipex);
	waitpid(child_1, NULL, 0);
	waitpid(child_2, NULL, 0);
	free_struct(&pipex);
	return (0);
}
