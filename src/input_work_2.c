/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_work_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:12:01 by ttokesi           #+#    #+#             */
/*   Updated: 2022/01/23 21:54:08 by ttokesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	error(char *error)
{
	perror(error);
	exit (EXIT_FAILURE);
}

void	execute_cmd(t_tok *tokdat)
{
	int		i;
	char	*path;
	char	*command;

	i = 0;
	// command = ft_split(cmd, ' ');
	command = tokdat->tokensfull[0];
	while (tokdat->data->paths[i])
	{
		path = ft_strjoin(tokdat->data->paths[i], "/");
		path = ft_strjoin(path, command);
		// printf("%s\n", path);
		if (access(path, F_OK) == 0)
		{
			if (execve(path, &tokdat->tokensfull[0], tokdat->data->environ) == -1)
				printf("error\n");
				// error("execve Error\n");
		}
		i++;
		free(path);
	}
	free(path);
	// ft_free_array(command);
	// error("Command not found");
}

int input_two(t_tok *tokdat)
{
	// pid_t	pid;

	// pid = fork();
	// if (pid == -1)
	// 	error("fork process creator Error\n");
	int i;

	i = 0;
	while (tokdat->tokensfull[i])
	{
		printf("%s\n", tokdat->tokensfull[i]);
		i++;
	}
	execute_cmd(tokdat);
	return (1);
}