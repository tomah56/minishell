/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:23:32 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/30 02:08:12 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_pwd(t_data *data)
{
	char	**temp_env;
	char	*path_pwd;
	char	**pwd;
	int		i;

	*temp_env = *data->environ;
	pwd = NULL;
	while (*temp_env != NULL && ft_strncmp(*temp_env, "PWD=", 4))
		(*temp_env)++;
	path_pwd = (*temp_env + 4);
	pwd = ft_split(path_pwd, ':');
	if (!pwd)
		msg_exit(data, "malloc error");
	i = 0;
	while (pwd[i] != NULL)
	{
		printf("%s\n", pwd[i]);
		i++;
	}
	ft_free_array(pwd);
	free((void *) pwd[i]);
}
