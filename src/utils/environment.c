/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:49:36 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/11 18:31:18 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// saves all environment variables
void	create_environment(t_data *data, char **env)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (env[len])
		len++;
	data->environ = ft_calloc(len + 1, sizeof(char *));
	if (data->environ == NULL)
		msg_exit(data, "malloc error");
	while (env[i])
	{
		data->environ[i] = ft_strdup(env[i]);
		if (data->environ[i] == NULL)
			msg_exit(data, "malloc error");
		i++;
	}
	// printf("len = %d\n", len);
	// i = 0;
	// while (i < 28)
	// {
	// 	printf("env = %s\n", data->environ[i]);
	// 	i++;
	// }
}

// finds path in envp and saves it
void	save_paths(t_data *data)
{
	char	*path_envp;
	// int		i;

	while (*data->environ != NULL && ft_strncmp(*data->environ, "PATH=", 5))
		++data->environ;
	if (*data->environ == NULL && data->dpflag == 0)
		msg_exit(data, "No such file or directory\n");
	if (data->dpflag == 1)
		data->paths = NULL;
	else
	{
		path_envp = (*data->environ + 5);
		data->paths = ft_split(path_envp, ':');
		if (!data->paths)
			msg_exit(data, "malloc error");
	}
}
