/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mi_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 21:26:09 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/17 21:26:09 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_end(char (*buf)[1 + 1])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*buf)[i] != '\n' && (*buf)[i] != '\0')
		i++;
	if ((*buf)[i] == '\n')
	{
		while (j < 1 - i)
		{
			(*buf)[j] = (*buf)[i + j + 1];
			j++;
		}
		(*buf)[j] = '\0';
		return (1);
	}
	return (0);
}

static void	sup_free(char **superholder)
{
	if (*superholder != NULL)
	{
		free(*superholder);
		*superholder = NULL;
	}
}

static char	*save_and_staff(char (*buf)[1 + 1], char **superholder)
{
	char	*temp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = -1;
	while (((*buf)[i - 1] != '\n' || i == 0) && (*buf)[i])
		i++;
	while ((*superholder) != NULL && (*superholder)[j])
		j++;
	temp = malloc((i + j + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	while (++k < j)
		temp[k] = (*superholder)[k];
	k = -1;
	while (++k < i)
		temp[k + j] = (*buf)[k];
	temp[k + j] = '\0';
	sup_free(superholder);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	buf[1 + 1];
	char		*superholder;
	int			size;

	size = 1;
	superholder = NULL;
	if (fd < 0)
		return (NULL);
	while (size)
	{
		if (buf[0])
		{
			superholder = save_and_staff(&buf, &superholder);
			if (check_end(&buf))
				return (superholder);
		}
		size = read(fd, buf, 1);
		if (size < 0)
			return (0);
		buf[size] = '\0';
	}
	return (superholder);
}
