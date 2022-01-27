/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:10:28 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/26 20:07:57 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	save_variable_in_environ(t_data *data, char **command, int i)
{
	char	*var;

	var = ft_substr(command[i], 0, ft_strlen(command[i]));
	if (var == NULL)
		msg_exit(data, "malloc error");
	//to be done
}

void	builtin_export(t_data *data)
{
	int		i;
	t_cmds	*current_cmd;
	char	**command;

	current_cmd = data->actual;
	command = current_cmd->commands;
	if (count_tokens(current_cmd) == 1)
		export_only(data);
	else if (count_tokens(current_cmd) > 1)
	{
		while (command[i] != NULL)
		{
			if (command[i][0] == '=')
			{
				printf("`%s'", command[i]);
				msg_exit(data, ": not a valid identifier");
			}
			if (ft_strchr(command[i], '=') != NULL)
				save_variable_in_environ(data, command, i);
			i++;
		}
	}
	else
		msg_exit(data, "no input");
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
	i = 0;
	while (exp[i] != NULL)
	{
		printf("declare -x %s\n", exp[i]);
		i++;
	}
	ft_free_array(exp);
}
