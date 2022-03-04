/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:51:51 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/01 00:02:19 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_unset(t_data *data)
{
	t_cmds	*current_cmd;
	char	**command;
	int		i;
	int		to_delete;

	i = 1;
	current_cmd = data->actual;
	command = current_cmd->commands;
	if (current_cmd->comandcount == 1)
		error_msg_no("not enough arguments\n");
	else if (current_cmd->comandcount > 1)
	{
		while (command[i] != NULL)
		{
			if (ft_strchr(command[i], '=') != NULL)
				msg_exit(data, "not a valid identifier\n");
			i++;
		}
		to_delete = check_valid_var(data, command);
		if (to_delete != FAILED)
			delete_var_env(data, command, to_delete);
	}
	// i = 0;
	// while (i < 5)
	// {
	// 	printf("333 = %s\n", data->environ[i]);
	// 	i++;
	// }
}

int	check_valid_var(t_data *data, char **command)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	while (command[i] != NULL)
	{
		j = 0;
		len = ft_strlen(command[i]);
		while (data->environ[j])
		{
			if (ft_strncmp(data->environ[j], command[i], len) == 0
				&& data->environ[j][len] == '=')
				return (i);
			j++;
		}
		i++;
	}
	g_exit = 0;
	return (-1);
}

void	delete_var_env(t_data *data, char **command, int i)
{
	int		j;
	int		len;

	j = 0;
	len = ft_strlen(command[i]);
	while (data->environ[j] != NULL)
	{
		if (ft_strncmp(data->environ[j], command[i], len) == 0
			&& data->environ[j][len] == '=')
		{
			ft_free_2array((void **) &data->environ[j]);
			while (data->environ[j + 1] != NULL)
			{
				data->environ[j] = data->environ[j + 1];
				j++;
			}
			data->environ[j] = NULL;
		}
		j++;
	}
}
