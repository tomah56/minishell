/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:52:50 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/31 23:06:50 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	argument_is_nbr(char *cmd_array)
{
	int	i;

	i = 0;
	while (cmd_array && cmd_array[i])
	{
		if (ft_is_plus_minus(cmd_array[i]))
			i++;
		if (!ft_isdigit(cmd_array[i]))
			return (FAILED);
		i++;
	}
	return (SUCCESS);
}

int	exit_errors(t_data *data, char **cmd_array)
{
	if (data->actual->comandcount > 1
		&& (argument_is_nbr(cmd_array[1]) == FAILED))
	{
		write(STDERR_FILENO, "bash: exit: ", 12);
		write(STDERR_FILENO, cmd_array[1], ft_strlen(cmd_array[1]));
		write(STDERR_FILENO, ": ", 2);
		ft_putstr_fd("numeric argument required\n", STDERR_FILENO);
		return (255);
	}
	else if (data->actual->comandcount > 2)
	{
		write(STDERR_FILENO, "bash: exit: ", 12);
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else
		return (0);
}

void	builtin_exit(t_data *data)
{
	int		exit_status;
	char	**cmd_array;

	exit_status = g_exit;
	write(STDERR_FILENO, "exit\n", 5);
	cmd_array = data->actual->commands;
	if (data->actual->comandcount == 2)
		exit_status = ft_atoi_long_long(cmd_array[1]);
	if (cmd_array[1] == NULL)
		g_exit = exit_status;
	else
		exit_status = exit_errors(data, cmd_array);
	ft_free_3array(&data->environ);
	data->environ = NULL;
	free_struct(data);
	data->environ = NULL;
	g_exit = exit_status;
	system("leaks minishellll");       // leakhunt
		fscanf(stdin, "c");
	exit(g_exit);
}
