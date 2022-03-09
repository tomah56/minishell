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

int	check_valid_var_2(t_data *data, char *command)
{
	int	j;
	int	len;

	while (command != NULL)
	{
		j = 0;
		len = ft_strlen(command);
		while (data->environ[j])
		{
			if (ft_strncmp(data->environ[j], command, len) == 0)
				return (j);
			j++;
		}
	}
	g_exit = 0;
	return (-1);
}

void	delete_var_env_2(t_data *data, char *cmd, int j)
{
	int		len;

	len = ft_strlen(cmd);
	while (data->environ[j] != NULL)
	{
		if (ft_strncmp(data->environ[j], cmd, len) == 0)
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

void	check_for_existing_variable(t_data *data, char *cmd)
{
	int	i;
	int	to_delete;

	i = 0;
	while (cmd[i] != '=')
		i++;
	cmd = ft_substr(cmd, 0, i);
	while (data->environ[i])
	{
		if (ft_strncmp(data->environ[i], cmd, ft_strlen(cmd)) == 0)
		{
			to_delete = check_valid_var_2(data, cmd);
			if (to_delete != FAILED)
				delete_var_env_2(data, cmd, to_delete);
		}
		i++;
	}
}

void	builtin_export(t_data *data)
{
	int		i;
	t_cmds	*current_cmd;
	char	**cmd;

	i = 0;
	current_cmd = data->actual;
	cmd = current_cmd->commands;
	if (current_cmd->comandcount == 1)
		export_only(data);
	else if (current_cmd->comandcount > 1)
	{
		while (cmd[i] != NULL)
		{
			if (cmd[i][0] == '=' || (ft_nr_spec(cmd[i][0]) && cmd[i][0] != '_'))
			{
				error_msg_no("not a valid identifier\n");
				break ;
			}
			if (ft_strchr(cmd[i], '=') != NULL)
				save_variable_in_environ(data, cmd, i);
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
		i++;
	data->environ = ft_calloc(i + 2, sizeof(char *));
	if (data->environ == NULL)
		msg_exit(data, "malloc error");
	i = 0;
	while (new_environ[i])
	{
		data->environ[i] = ft_strdup(new_environ[i]);
		i++;
	}
	data->environ[i] = NULL;
	ft_free_3array(&new_environ);
	new_environ = NULL;
}

static int	count_size_environ(t_data *data)
{
	int		len;

	len = 0;
	while (data->environ[len])
		len++;
	return (len);
}

void	save_variable_in_environ(t_data *data, char **command, int i)
{
	char	*var;
	char	**new_environ;
	int		len;
	int		j;

	len = count_size_environ(data);
	var = ft_substr(command[i], 0, ft_strlen(command[i]));
	check_for_existing_variable(data, command[i]);
	new_environ = ft_calloc(len + 2, sizeof(char *));
	if (var == NULL || new_environ == NULL)
		msg_exit(data, "malloc error");
	j = 0;
	while (data->environ[j] != NULL)
	{
		new_environ[j] = ft_strdup(data->environ[j]);
		j++;
	}
	new_environ[j] = ft_strdup(var);
	new_environ[j + 1] = NULL;
	free(var);
	ft_free_3array(&data->environ);
	data->environ = NULL;
	copy_to_environ(data, new_environ);
	g_exit = 0;
}
