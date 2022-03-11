/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 23:27:07 by sreinhol          #+#    #+#             */
/*   Updated: 2022/03/09 21:33:59 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		exp[i] = NULL;
		exp = sort_env(exp);
	}
	print_export(exp);
	ft_free_array(exp);
	g_exit = 0;
}

char	**sort_env(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (env[i] != NULL)
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

static int	check_valid_var_2(t_data *data, char *command)
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

static void	delete_var_env_2(t_data *data, char *cmd, int j)
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
