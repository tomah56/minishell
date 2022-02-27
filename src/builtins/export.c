/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:10:28 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/31 23:59:35 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_export(t_data *data)
{
	int		i;
	t_cmds	*current_cmd;
	char	**command;

	i = 0;
	current_cmd = data->actual;
	command = current_cmd->commands;
	if (current_cmd->comandcount == 1)
		export_only(data);
	else if (current_cmd->comandcount > 1)
	{
		while (command[i] != NULL)
		{
			if (command[i][0] == '=')
				msg_exit(data, "not a valid identifier");
			if (ft_strchr(command[i], '=') != NULL)
				save_variable_in_environ(data, command, i);
			i++;
		}
	}
	else
		msg_exit(data, "no input");
}

static void	copy_to_environ(t_data *data, char **new_environ)
{
	int	i;

	i = 0;
	while (new_environ[i])
	{
		data->environ[i] = new_environ[i];
		i++;
	}
}

void	save_variable_in_environ(t_data *data, char **command, int i)
{
	char	*var;
	char	**new_environ;
	int		len;
	int		j;

	len = 0;
	while (data->environ[len])
		len++;
	var = ft_substr(command[i], 0, ft_strlen(command[i]));
	new_environ = ft_calloc(len + 2, sizeof(char *));
	if (var == NULL || new_environ == NULL)
		msg_exit(data, "malloc error");
	j = 0;
	while (data->environ[j] != NULL)
	{
		new_environ[j] = data->environ[j];
		j++;
	}
	new_environ[j] = ft_strdup(var);
	new_environ[j + 1] = NULL;
	free(var);
	copy_to_environ(data, new_environ);
	g_exit = 0;
}

char	**sort_env(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (env[i] != NULL && env[i + 1] != NULL)
	{
		j = i + 1;
		while (env[j] != NULL)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp = ft_strdup(env[i]);
				if (temp == NULL)
					ft_free_array(env);
				free(env[i]);
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (env);
}
