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

#include "../../include/minishell.h"

void	error_msg_no(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

void	error_msg(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	perror("");
}

void	msg_exit(t_data *data, char *msg)
{
	free_struct(data);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void	dup_exit(t_data *data, char *msg)
{
	free_struct(data);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	perror("");
	exit(EXIT_FAILURE);
}

void	cmd_not_found_error(t_data *data, char *msg)
{
	free_struct(data);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(127);
}
