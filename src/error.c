/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:02:34 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/11 13:44:17 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	msg_exit(t_data *data, char *msg)
{
	free_struct(data);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void	free_struct(t_data *data)
{
	if (data != NULL)
	{
		if (data->environ != NULL)
			ft_free_array(data->environ);
	}
}
