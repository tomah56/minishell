/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:52:50 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/30 23:12:15 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_exit(t_data *data)
{
	write(STDERR_FILENO, "exit\n", 5);
		
}


	// if (data->actual->next != NULL) //when there is a next cmd, exit does nothing