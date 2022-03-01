/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:52:29 by sreinhol          #+#    #+#             */
/*   Updated: 2022/03/01 23:10:08 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_dup(t_data	*data, int fd)
{
	int	ret_fd;

	ret_fd = dup(fd);
	if (ret_fd == FAILED)
		dup_exit(data, "dup error ");
	return (ret_fd);
}

void	ft_dup2(t_data	*data, int fd1, int fd2)
{
	if (dup2(fd1, fd2) == FAILED)
		dup_exit(data, "2dup error ");
}

void	ft_close(t_data	*data, int fd)
{
	if (close(fd) == FAILED)
		msg_exit(data, "close error\n");
}

