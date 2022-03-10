/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:09:05 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/31 23:57:41 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	path_not_found_error(char *msg, char *str)
{
	write(STDERR_FILENO, "!(hakuna matata): ", 18);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	g_exit = 127;
}

void	builtin_env(t_data *data)
{
	int		i;
	bool	unset;

	i = 0;
	unset = true;
	while (data->environ[i] != NULL)
	{
		if (!ft_strncmp(data->environ[i], "PATH=", 5))
			unset = false;
		i++;
	}
	if (unset == false)
	{
		i = 0;
		while (data->environ[i] != NULL)
		{
			printf("%s\n", data->environ[i]);
			i++;
		}
		g_exit = 0;
	}
	else
		path_not_found_error(" No such file or directory\n", "env");
}
