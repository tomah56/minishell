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

int	here_doc(char *stop, t_data *data, char *name)
{
	char	*temp;
	int		size;
	int		fd;

	signal(SIGINT, rec_sig_doc);
	if (stop == NULL)
	{
		write(2, "ERROR\n", 6);
		return (-1); // bash: syntax error near unexpected token `newline'
	}
	fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd == FAILED)
	{
		write(2, "ERROR\n", 6); // temperarrly
		return (-1);
	}
	size = ft_strlen(stop);
	temp = readline(">");
	if (temp == NULL)
	{
		ft_close(data, fd);
		return (-1);
	}
	while (ft_strncmp(temp, stop, size) || temp[size] != '\0')
	{
		temp = no_expand_next_part_no(temp, data);
		write(fd, temp, ft_strlen(temp));
		write(fd, "\n", 1);
		temp = readline(">");
		if (temp == NULL)
		{
			close(fd);
			return (-1);
		}
	}
	close(fd);
	fd = open(name, O_RDONLY, 0777);
	return (fd);
}
