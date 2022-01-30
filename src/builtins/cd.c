/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:43:42 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/30 01:31:00 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	if (current_cmd->comandcount == 1)
		cd_only(data);
	else if (current_cmd->comandcount > 1)
	{
		if (chdir(command[1]) == -1)
		{
			printf("`%s'", command[1]);
			msg_exit(data, ": No such file or directory");
		}
	}
	change_var_env(data, "OLDPWD=", cwd);
	new = NULL;
	new = getcwd(new, 0);
	change_var_env(data, "PWD=", new);
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
		msg_exit(data, "cd error: home not set\n");
	}
	change_var_env(data, "OLDPWD=", cwd);
	change_var_env(data, "PWD=", home);
}

char	*get_home(t_data *data)
{
	char	*home;

	while (*data->environ != NULL && ft_strncmp(*data->environ, "HOME=", 5))
		++data->environ;
	if (*data->environ == NULL)
		msg_exit(data, "error");
	home = (*data->environ + 5);
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
		msg_exit(data, "malloc error");
	while (data->environ[i] != NULL
		&& ft_strncmp(data->environ[i], var_name, len))
		i++;
	free((void *) data->environ[i]);
	data->environ[i] = new;
}
