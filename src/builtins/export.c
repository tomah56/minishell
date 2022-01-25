/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:10:28 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/25 23:32:50 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_execute(t_data *data)
{
	int		i;
	t_cmds	*current_cmd;

	current_cmd = data->cmds;
	if (count_tokens(data) == 1) //need to change function for current command (now it just counts first command)
		export_only(data);
	else
	{
		//check if first char after export is =, if yes then error "": not a valid identifier"
		//otherwise check if = is found
		//if no = then nothing is to be done and no error
		//when = is found then put it in environ
	}
}

void	sort_env(char **env)
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
				{
					ft_free_array(env);
				}
				free(&env[i]);
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
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
		while (exp[i])
		{
			exp[i] = ft_strdup(data->environ[i]);
			i++;
		}
		sort_env(exp);
	}
}
