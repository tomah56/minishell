/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:47:25 by sreinhol          #+#    #+#             */
/*   Updated: 2022/03/06 16:58:17 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_cmd(t_data *data, t_cmds *temp_c, int i)
{
	char	*path;

	if (temp_c->builtin == true)
		execute_builtin(data, temp_c);
	else
	{
		save_paths(data);
		i = 0;
		if (data->dpflag == 0)
		{
			while (data->paths[i])
				i = exec_cmd_helper(data, temp_c->commands, i);
		}
		else
			exec_cmd_helper_2(data, temp_c, temp_c->commands);
		cmd_not_found_error(data, "Command not found\n");
	}
}

int	exec_cmd_helper(t_data *data, char **command, int i)
{
	char	*path;

	path = slash_join(data->paths[i], command[0]);
	if (access(path, F_OK) == SUCCESS)
	{
		if (execve(path, &command[0], data->environ) == FAILED)
			msg_exit(data, "execve Error\n");
	}
	i++;
	free(path);
	return (i);
}

void	exec_cmd_helper_2(t_data *data, t_cmds *temp_c, char **command)
{
	char	*path;

	path = temp_c->defpath;
	if (access(path, F_OK) == SUCCESS)
	{
		if (execve(path, &command[0], data->environ) == FAILED)
			msg_exit(data, "execve Error 2\n");
		free(path);
	}
	path = NULL;
}
