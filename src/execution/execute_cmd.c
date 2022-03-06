/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:50:27 by sreinhol          #+#    #+#             */
/*   Updated: 2022/03/06 16:01:22 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	cmd_exec_helper(t_data *data, t_cmds *temp_c, int i)
{
	char	*path;
	char	**command;

	while (data->paths[i])
	{
		path = slash_join(data->paths[i], command[0]);
		if (access(path, F_OK) == SUCCESS)
		{
			if (execve(path, &command[0], data->environ) == FAILED)
				msg_exit(data, "execve Error\n");
		}
		i++;
		free(path);
	}
}

void	execute_cmd(t_data *data, t_cmds *temp_c, int i)
{
	char	**command;
	char	*path;

	if (temp_c->builtin == true)
		execute_builtin(data, temp_c);
	else
	{
		save_paths(data);
		command = malloc((count_tokens(temp_c) + 1) * sizeof(char *));
		while (temp_c->commands[i])
		{
			command[i] = temp_c->commands[i];
			i++;
		}
		i = 0;
		if (data->dpflag == 0)
			cmd_exec_helper(data, temp_c, i);
		else
		{
			path = temp_c->defpath;
			if (access(path, F_OK) == SUCCESS)
			{
				if (execve(path, &command[0], data->environ) == FAILED)
					msg_exit(data, "execve Error 2\n");
				free(path);
			}
		}
		path = NULL;
		cmd_not_found_error(data, "Command not found\n");
	}
}
