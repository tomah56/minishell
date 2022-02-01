#include "../include/minishell.h"


int	size_dollar_point(char **str, t_data *data)
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

char *next_part(char **str, t_data *data)
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
	int		size;

	if (str == NULL)
		return (NULL);
	size = 1;
	superholder = NULL;
	data->qudouble = 0;
	data->qusingle = 0;
	while (*str != '\0')
	{
		// check_token_flags_li(*str, data);
		buf = next_part(&str, data);
		if (buf[0])
		{
			// superholder = save_and_staff(&buf, &superholder);
			if (superholder == NULL)
				superholder = ft_strdup(buf);
			else
				superholder = ft_strjoin(superholder, buf);
			// if (check_end(&buf))
			// 	return (superholder);
		}



		// if (size < 0)
		// 	return (0);
		// str++;
	}
	return (superholder);
	// return (buf);
}