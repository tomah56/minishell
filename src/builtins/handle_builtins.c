/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:16:59 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/02 21:17:20 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_for_builtins(t_data *data)
{
	t_cmds	*cmd;

	cmd = data->cmds;
	while (cmd)
	{
		if (ft_strncmp(cmd->commands[0], "cd", 3) == SUCCESS)
			cmd->builtin = true;
		else if (ft_strncmp(cmd->commands[0], "echo", 5) == SUCCESS)
			cmd->builtin = true;
		else if (ft_strncmp(cmd->commands[0], "env", 4) == SUCCESS)
			cmd->builtin = true;
		else if (ft_strncmp(cmd->commands[0], "exit", 5) == SUCCESS)
			cmd->builtin = true;
		else if (ft_strncmp(cmd->commands[0], "export", 7) == SUCCESS)
			cmd->builtin = true;
		else if (ft_strncmp(cmd->commands[0], "pwd", 4) == SUCCESS)
			cmd->builtin = true;
		else if (ft_strncmp(cmd->commands[0], "unset", 6) == SUCCESS)
			cmd->builtin = true;
		else
			cmd->builtin = false;
		cmd = cmd->next;
	}
}

void	execute_builtin(t_data *data)
{
	if (ft_strncmp(data->cmds->commands[0], "cd", 3) == SUCCESS)
		builtin_cd(data);
	else if (ft_strncmp(data->cmds->commands[0], "echo", 5) == SUCCESS)
		builtin_echo(data);
	else if (ft_strncmp(data->cmds->commands[0], "env", 4) == SUCCESS)
		builtin_env(data);
	else if (ft_strncmp(data->cmds->commands[0], "exit", 5) == SUCCESS)
		builtin_exit(data);
	else if (ft_strncmp(data->cmds->commands[0], "export", 7) == SUCCESS)
		builtin_export(data);
	else if (ft_strncmp(data->cmds->commands[0], "pwd", 4) == SUCCESS)
		builtin_pwd(data);
	else if (ft_strncmp(data->cmds->commands[0], "unset", 6) == SUCCESS)
		builtin_unset(data);
}
