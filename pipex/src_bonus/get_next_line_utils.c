/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:59:16 by sreinhol          #+#    #+#             */
/*   Updated: 2021/12/26 21:21:41 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	*ft_free(char *line)
{
	free(line);
	return (NULL);
}

char	line_end(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	line_len(char *save)
{
	int	i;

	i = 0;
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	if (save[i] == '\n')
		i++;
	return (i);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	size_t					i;
	unsigned int			size;
	char					*src;
	char					*dst;

	src = s;
	size = len + 1;
	dst = malloc(sizeof(char) * (size + 1));
	if (!src || dst == NULL)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (dst);
	i = 0;
	while (i <= len && s[i] != '\0')
	{
		dst[i] = src[i + start];
		i++;
	}
	dst[len] = '\0';
	return (dst);
}
