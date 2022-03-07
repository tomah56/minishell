/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 21:09:07 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/17 21:09:07 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_clean_dollar(char *str, t_data *data)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (data->environ[i] != NULL)
	{	
		if (!ft_strncmp(data->environ[i], str + 1, ft_strlen(str) - 1)
			&& data->environ[i][ft_strlen(str) - 1] == '=')
		{
			temp = malloc(ft_strlen(data->environ[i]) - ft_strlen(str) + 1);
			j = ft_strlen(str) - 1;
			while (data->environ[i][j++] != '\0')
				temp[j - ft_strlen(str)] = data->environ[i][j];
			temp[j - ft_strlen(str)] = '\0';
			free(str);
			return (temp);
		}
		i++;
	}
	free(str);
	return (NULL);
}

static int	size_dollar_point_helper(char **str, t_data *data, int len)
{
	while ((**str != '$' && **str != '\0' ) || data->qusingle == 1)
	{
		check_token_flags_li(**str, data);
		len++;
		(*str)++;
	}
	return (len);
}

static int	size_dollar_point(char **str, t_data *data, int len)
{
	if ((**str == '$' && data->qusingle == 0))
	{
		len++;
		(*str)++;
		if (**str == '?')
		{
			len++;
			(*str)++;
		}
		else
		{
			while (ft_isalnum(**str) == 1 && **str != '\0')
			{
				len++;
				(*str)++;
			}
		}
	}
	else
		len = size_dollar_point_helper(str, data, len);
	return (len);
}

static char	*next_part(char **str, t_data *data)
{
	char	*buf;
	char	*temp;
	int		len;

	temp = *str;
	len = size_dollar_point(str, data, 0);
	if (*temp == '$' && data->qusingle == 0 && len > 1)
	{
		if (temp[1] == '?')
		{
			buf = ft_itoa(g_exit);
		}
		else
			buf = expand_clean_dollar(ft_substr(temp, 0, len), data);
	}
	else
		buf = ft_substr(temp, 0, len);
	return (buf);
}

char	*expand_next_part(char *str, t_data *data)
{
	char	*buf;
	char	*superholder;

	if (str == NULL)
		return (NULL);
	superholder = NULL;
	data->qudouble = 0;
	data->qusingle = 0;
	while (*str != '\0')
	{
		buf = next_part(&str, data);
		if (buf != NULL)
		{
			if (superholder == NULL)
				superholder = ft_strdup(buf);
			else
				superholder = ft_strjoin(superholder, buf);
		}
	}
	free(buf);
	return (superholder);
}
