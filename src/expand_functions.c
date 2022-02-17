#include "../include/minishell.h"

char	*expand_clean_dollar(char *str, t_data *data)
{
	char	*temp;
	int		i;
	int		j;
	int		size;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (data->environ[i] != NULL)
	{	
		size = ft_strlen(str);
		if (!ft_strncmp(data->environ[i], str + 1, size - 1) && data->environ[i][size - 1] == '=')
		{
			temp = malloc(ft_strlen(data->environ[i]) - size + 1);
			j = size - 1;
			while (data->environ[i][j++] != '\0')
				temp[j - size] = data->environ[i][j];
			temp[j - size] = '\0';
			free(str);
			return (temp);
		}
		i++;
	}
	free(str);
	return (NULL);
}

static int	size_dollar_point(char **str, t_data *data)
{
	int len;

	len = 0;
	if ((**str == '$' && data->qusingle == 0))
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
		while ((**str != '$' && **str != '\0' )|| data->qusingle == 1)
		{
			check_token_flags_li(**str, data);
			len++;
			(*str)++;
		}
	}
	return (len);
}

static char *next_part(char **str, t_data *data)
{
	char *buf;
	char *temp;
	int len;

	temp = *str;
	len = size_dollar_point(str, data);
	if (*temp == '$'&& data->qusingle == 0)
	{
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