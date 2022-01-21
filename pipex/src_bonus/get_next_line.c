/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:58:31 by sreinhol          #+#    #+#             */
/*   Updated: 2021/12/27 01:43:01 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#define BUFFER_SIZE 100

char	*ft_linejoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	ft_free((char *)s1);
	return (str);
}

char	*next_line(char *str, int start)
{
	char	*s;
	int		i;

	i = 0;
	if (!str || !str[start] || !str[i])
		return (ft_free(str));
	s = malloc(sizeof(char) * ((ft_strlen(str) - start) + 1));
	if (!s)
		return (0);
	i = 0;
	while (str[start] != '\0')
	{
		s[i] = str[start];
		i++;
		start++;
	}
	s[i] = '\0';
	ft_free(str);
	return (s);
}

char	*read_loop(int fd, char *line, char *save, int rread)
{
	while (!line_end(save) && rread > 0)
	{
		rread = read(fd, line, BUFFER_SIZE);
		if ((rread == 0 && !save) || (rread == -1))
			return (ft_free(line));
		line[rread] = '\0';
		save = ft_linejoin(save, line);
	}
	ft_free(line);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	int			rread;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = ((char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)));
	if (!line)
		return (0);
	rread = 42;
	save = read_loop(fd, line, save, rread);
	if (!save)
		return (0);
	i = line_len(save);
	line = ft_substr_gnl(save, 0, i);
	save = next_line(save, i);
	return (line);
}
