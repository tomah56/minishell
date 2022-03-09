/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:43:42 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/08 21:35:40 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	error(t_data *data, char *str, char *cwd)
{
	error_msg_no(str);
	error_msg(": ");
	free(cwd);
	free_struct(data);
	g_exit = EXIT_FAILURE;
}

void	builtin_cd(t_data *data)
{
	t_cmds	*current_cmd;
	char	**command;
	char	*cwd;
	char	*new;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	current_cmd = data->actual;
	command = current_cmd->commands;
	if (current_cmd->comandcount == 1 || ft_strchr(command[1], '~') != NULL)
		cd_only(data);
	else if (current_cmd->comandcount > 1)
	{
		if (chdir(command[1]) == -1)
			error(data, command[1], cwd);
		change_var_env(data, "OLDPWD=", cwd);
		new = NULL;
		new = getcwd(new, 0);
		change_var_env(data, "PWD=", new);
		g_exit = 0;
	}
}

void	cd_only(t_data *data)
{
	char	*cwd;
	char	*home;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	home = get_home(data);
	if (chdir(home) == -1)
	{
		error_msg_no("cd error: HOME not set\n");
		return ;
	}
	change_var_env(data, "OLDPWD=", cwd);
	change_var_env(data, "PWD=", home);
	g_exit = 0;
}

char	*get_home(t_data *data)
{
	char	*home;
	char	*save;

	save = *data->environ;
	while (*data->environ != NULL && ft_strncmp(*data->environ, "HOME=", 5))
		++data->environ;
	if (*data->environ == NULL)
	{
		free_struct(data);
		g_exit = EXIT_FAILURE;
		return (NULL);
	}
	home = (*data->environ + 5);
	while (ft_strncmp(*data->environ, save, ft_strlen(save)))
		--data->environ;
	return (home);
}

void	change_var_env(t_data *data, char *var_name, char *new_var)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var_name);
	new_var = ft_strjoin(var_name, new_var);
	new = ft_strdup(new_var);
	free(new_var);
	if (new == NULL)
		msg_exit(data, "malloc error\n");
	while (data->environ[i] != NULL
		&& ft_strncmp(data->environ[i], var_name, len))
		i++;
	free((void *) data->environ[i]);
	data->environ[i] = new;
}
