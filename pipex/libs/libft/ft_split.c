/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 19:02:38 by sreinhol          #+#    #+#             */
/*   Updated: 2021/12/19 23:36:36 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

static int	count_substr(char const *str, char c)
{
	int	i;
	int	counter;
	int	delim;

	i = 0;
	counter = 0;
	delim = c;
	while (str[i])
	{
		while (str[i] && (str[i] == delim))
			i++;
		if (str[i] && (str[i] != delim))
		{
			while (str[i] != delim && str[i] != '\0')
				i++;
			counter++;
		}
	}
	return (counter);
}

static int	count_substrlen(char const *str, int i, char c)
{
	int	counter;

	counter = 0;
	while (str[i] != c && str[i] != '\0')
	{
		counter++;
		i++;
	}
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	int		j;
	int		l;

	i = 0;
	l = 0;
	if (!s)
		return (NULL);
	result = malloc((count_substr(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			j = count_substrlen(s, i, c);
			result[l++] = ft_substr(s, i, j);
			i = i + j;
		}
	}
	return (result);
}
