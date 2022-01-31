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

void	builtin_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->environ[i] != NULL)
	{
		printf("%s\n", data->environ[i]);
		i++;
	}
	g_exit = 0;
}
