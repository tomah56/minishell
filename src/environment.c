/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:49:36 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/22 19:16:17 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

