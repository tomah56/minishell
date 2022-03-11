/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 22:28:45 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/01 23:09:03 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	normy_baby(char	**cmd_array, int *i)
{
	bool	newline;

	newline = true;
	while (cmd_array[1 + *i] && !ft_strncmp(cmd_array[1 + *i], "-n", 3))
	{
		newline = false;
		(*i)++;
	}
	if (newline == true && cmd_array[1][0] == '-')
	{
		while (cmd_array[1][*i + 1] == 'n')
			(*i)++;
		if (cmd_array[1][*i + 1] == '\0')
			newline = false;
		*i = 1;
	}
	return (newline);
}

void	builtin_echo(t_data *data)
{
	char	**cmd_array;
	bool	newline;
	int		i;

	cmd_array = data->actual->commands;
	i = 0;
	newline = normy_baby(data->actual->commands, &i);
	while (cmd_array[1 + i])
	{
		printf("%s", cmd_array[1 + i]);
		if (cmd_array[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	g_exit = 0;
}
