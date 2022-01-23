/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:49:36 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/23 21:07:42 by ttokesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
void	save_paths(t_data *data, char **env)
{
	char	*path_envp;
	int		i;

	while (*env != NULL && ft_strncmp(*env, "PATH=", 5))
		++env;
	if (*env == NULL)
		msg_exit(data, "malloc error");
	path_envp = (*env + 5);
	data->paths = ft_split(path_envp, ':');
	// i = 0;
	// while (data->paths[i])
	// {
	// 	printf("paths = %s\n", data->paths[i]);
	// 	i++;
	// }
	if (!data->paths)
		msg_exit(data, "malloc error");
}
