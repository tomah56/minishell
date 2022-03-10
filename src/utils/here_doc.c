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
		g_exit = 1;
		write(2, "\n", 1);
		rl_on_new_line();
		close(STDIN_FILENO);
	}
}

static int	unlink_close(t_data *data, int fd, char *name)
{
	unlink(name);
	g_exit = 0;
	if (close(fd) == FAILED)
		msg_exit(data, "close error\n");
	return (1);
}

static int	norm_fin_cut(char *name, char *temp, int fd)
{
	free(temp);
	close(fd);
	fd = open(name, O_RDONLY, 0777);
	return (fd);
}

int	here_doc(char *s, t_data *data, char *name)
{
	char	*temp;
	char	*temp1;
	int		fd;

	signal(SIGINT, rec_sig_doc);
	fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd == FAILED)
		return (-1);
	temp = readline(">");
	if (temp == NULL && unlink_close(data, fd, name))
		return (-1);
	while (ft_strncmp(temp, s, ft_strlen(s)) || temp[ft_strlen(s)] != '\0')
	{
		temp1 = temp;
		free(temp);
		temp = no_expand_next_part_no(temp1, data);
		write(fd, temp, ft_strlen(temp));
		write(fd, "\n", 1);
		free(temp);
		temp = readline(">");
		if (temp == NULL && unlink_close(data, fd, name))
			return (-1);
	}
	return (norm_fin_cut(name, temp, fd));
}
