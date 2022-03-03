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
		{
			cmd->builtin = true;
			cmd->exit = true;
		}
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

void	exec_builtins(t_data *data, t_cmds *cmds)
{
	if (ft_strncmp(cmds->commands[0], "cd", 3) == SUCCESS)
		builtin_cd(data);
	else if (ft_strncmp(cmds->commands[0], "echo", 5) == SUCCESS)
		builtin_echo(data);
	else if (ft_strncmp(cmds->commands[0], "env", 4) == SUCCESS)
		builtin_env(data);
	else if (ft_strncmp(cmds->commands[0], "exit", 5) == SUCCESS)
		builtin_exit(data);
	else if (ft_strncmp(cmds->commands[0], "export", 7) == SUCCESS)
		builtin_export(data);
	else if (ft_strncmp(cmds->commands[0], "pwd", 4) == SUCCESS)
		builtin_pwd(data);
	else if (ft_strncmp(cmds->commands[0], "unset", 6) == SUCCESS)
		builtin_unset(data);
}

void	execute_builtin(t_data *data, t_cmds *cmds)
{
	int	temp_in;
	int	temp_out;

	temp_in = ft_dup(data, STDIN_FILENO);
	temp_out = ft_dup(data, STDOUT_FILENO);
	//heredoc?
	if (cmds->infile != STDIN_FILENO && cmds->infile != -5)
		ft_dup2(data, cmds->infile, STDIN_FILENO);
	if (cmds->outfile != STDOUT_FILENO && cmds->outfile != -5)
		ft_dup2(data, cmds->outfile, STDOUT_FILENO);
	exec_builtins(data, cmds);
	ft_dup2(data, temp_in, STDIN_FILENO);
	ft_dup2(data, temp_out, STDOUT_FILENO);
	ft_close(data, temp_in);
	ft_close(data, temp_out);
	exit(g_exit);
}
