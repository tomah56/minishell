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
		msg_exit(data, "not enough arguments");
	else if (current_cmd->comandcount > 1)
	{
		while (command[i] != NULL)
		{
			if (ft_strchr(command[i], '=') != NULL)
			{
				printf("`%s'", command[i]);
				msg_exit(data, ": not a valid identifier");
			}
			i++;
		}
		to_delete = check_valid_var(data, command);
		if (to_delete != FAILED)
			data->environ = delete_var_env(data, command, to_delete, 0);
	}
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

char	**delete_var_env(t_data *data, char **command, int i, int j)
{
	char	**new_environ;
	int		len;
	int		k;

	while (data->environ[len])
		len++;
	k = 0;
	new_environ = ft_calloc(len - 1, sizeof(char *));
	if (new_environ == NULL)
		msg_exit(data, "malloc error");
	while (data->environ[j] != NULL)
	{
		if (ft_strncmp(data->environ[j], command[i], ft_strlen(command[i]))
			 == 0)
		{
			free((void *) data->environ[j]);
			j++;
		}
		new_environ[k] = data->environ[j];
		j++;
		k++;
	}
	new_environ[k + 1] = NULL;
	free(data->environ);
	return (new_environ);
}
