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
			{
				printf("`%s'", command[i]);
				msg_exit(data, ": not a valid identifier");
			}
			if (ft_strchr(command[i], '=') != NULL)
				save_variable_in_environ(data, command);
			i++;
		}
	}
	else
		msg_exit(data, "no input");
}

void	save_variable_in_environ(t_data *data, char **command)
{
	char	*var;
	char	**new_environ;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (data->environ[len])
		len++;
	var = ft_substr(command[i], 0, ft_strlen(command[i]));
	new_environ = ft_calloc(len + 2, sizeof(char *));
	if (var == NULL || new_environ == NULL)
		msg_exit(data, "malloc error");
	while (data->environ[i] != NULL)
	{
		new_environ[i] = data->environ[i];
		i++;
	}
	new_environ[i] = ft_strdup(var);
	new_environ[i + 1] = NULL;
	ft_free_array(data->environ);
	data->environ = new_environ;
	free(var);
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

void	export_only(t_data *data)
{
	char	**exp;
	int		i;

	if (data->environ[0] == NULL)
		return ;
	else
	{
		exp = ft_calloc(ft_strlen_double(data->environ) + 1, sizeof(char *));
		if (exp == NULL)
			msg_exit(data, "malloc error");
		i = 0;
		while (data->environ[i])
		{
			exp[i] = ft_strdup(data->environ[i]);
			i++;
		}
		exp = sort_env(exp);
	}
	print_export(data, exp);
	ft_free_array(exp);
	g_exit = 0;
}

void	print_export(t_data *data, char **exp)
{
	int		i;
	int		j;
	int		len;
	char	*var_name;
	char	*var;

	i = 0;
	while (exp[i] != NULL)
	{
		len = ft_strlen(exp[i]);
		j = 0;
		while (exp[i][j] && exp[i][j] != '=')
			j++;
		j = j + 1;
		var_name = ft_substr(exp[i], 0, j);
		var = ft_substr(exp[i], j, (len - j));
		printf("%s", var_name);
		printf("\"%s\"\n", var);
		free(var_name);
		free(var);
		i++;
	}
}
