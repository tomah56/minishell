/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_no_q_f_heredocfile.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 21:08:46 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/17 21:08:46 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	no_size_dollar_point(char **str, t_data *data)
{
	int	len;

	len = 0;
	if (**str == '$')
	{
			len++;
			(*str)++;
		while (ft_isalnum(**str) == 1 && **str != '\0')
		{
			len++;
			(*str)++;
		}
	}
	else
	{
		while ((**str != '$' && **str != '\0' ))
		{
			len++;
			(*str)++;
		}
	}
	return (len);
}

static char	*no_next_part(char **str, t_data *data)
{
	char	*buf;
	char	*temp;
	int		len;

	temp = *str;
	len = no_size_dollar_point(str, data);
	if (*temp == '$')
	{
		buf = expand_clean_dollar(ft_substr(temp, 0, len), data);
	}
	else
		buf = ft_substr(temp, 0, len);
	return (buf);
}

char	*no_expand_next_part_no(char *str, t_data *data)
{
	char	*buf;
	char	*superholder;

	if (str == NULL)
		return (NULL);
	superholder = NULL;
	while (*str != '\0')
	{
		buf = no_next_part(&str, data);
		if (buf != NULL)
		{
			if (superholder == NULL)
			{
				superholder = ft_strdup(buf);
				free(buf);
			}
			else
				superholder = ft_strjoin(superholder, buf);
		}
	}
	return (superholder);
}
