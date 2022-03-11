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

void	print_export(char **exp)
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

static void	save_variable_in_environ(t_data *data, char **command, int i)
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
