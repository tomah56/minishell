/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 20:54:40 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/12 14:38:24 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	rec_sig_doc(int num)
{
	rl_on_new_line();
	rl_redisplay();
	write(2, "  \b\b", 5);
	if (num == 2)
	{
		write(2, " ", 1);
		rl_on_new_line();
		close(STDIN_FILENO);
	}
}

static int	unlink_close(t_data *data, int fd, char *name)
{
	unlink(name);
	if (close(fd) == FAILED)
		msg_exit(data, "close error\n");
	return (1);
}

static int norm_fin_cut(char *name, char *temp, int fd)
{
	free(temp);
	close(fd);
	fd = open(name, O_RDONLY, 0777);
	return (fd);
}

int	here_doc(char *stop, t_data *data, char *name)
{
	char	*temp;
	char	*temp1;
	int		size;
	int		fd;

	signal(SIGINT, rec_sig_doc);
	fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd == FAILED)
		return (-1);
	size = ft_strlen(stop);
	temp = readline(">");
	if (temp == NULL && unlink_close(data, fd, name))
		return (-1);
	while (ft_strncmp(temp, stop, size) || temp[size] != '\0')
	{
		temp1 = temp;
		free(temp);
		temp = no_expand_next_part_no(temp1, data); // leak danger
		write(fd, temp, ft_strlen(temp));
		write(fd, "\n", 1);
		free(temp);
		temp = readline(">");
		if (temp == NULL && unlink_close(data, fd, name))
			return (-1);
	}
	free(stop);
	return (norm_fin_cut(name, temp, fd));
}
