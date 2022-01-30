#include "../include/minishell.h"

int	quote_cut_counter(char *str)
{
	int	i;
	int	j;
	int	qusig;
	int	qudou;

	i = 0;
	j = 0;
	qusig = 0;
	qudou = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && qudou % 2 == 0)
			qusig += 1;
		else if (str[i] == '\"' && qusig % 2 == 0)
			qudou += 1;
		else
			j++;
		i++;
	}
	return (j);
}

char	*quote_cutter(char *str, int qusig, int qudou)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	temp = malloc(quote_cut_counter(str) * sizeof(char));
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && qudou % 2 == 0)
			qusig += 1;
		else if (str[i] == '\"' && qusig % 2 == 0)
			qudou += 1;
		else
			temp[j++] = str[i];
		i++;
	}
	temp[j] = '\0';
	return (temp);
}



int check_quote_type_dollar(char *str)
{
	int	i;
	int temp;

	i = 0;
	temp = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
	{
		if (temp == 0 && str[i] == '\"')
			temp = QUDOUBLE;
		else if (temp == 0 && str[i] == '\'')
			return (QUSINGLE);
		else if (temp == QUDOUBLE && str[i] == '$')
			return (DOLLARQ);
		else if (temp == QUDOUBLE && str[i] == '\"')
			return (temp);
		i++;
	}
	return (temp);
}

t_s size_dollar(char *str)
{
	t_s size;
	int i;

	i = 0;
	size.length = 0;
	size.i = 0;
	size.j = 0;
	while (str[i] !='\0')
	{
		if (size.length != 0 && (str[i] == '\'' || str[i] == '\"' || str[i] == '$'))
			break ;
		if (str[i] == '$' || size.length != 0)
			size.length++;
		if (str[i] == '$')
			size.start = i;
		i++;
	}
	return (size);
}

char *expand_dirt_dollar(char *str, t_data *data)
{
	char *temp;
	char *tempfull;
	t_s siz;
	// while

	//siz = size_dollar(str + siz.start + siz.length); 
	siz = size_dollar(str);
	temp = expand_clean_dollar(ft_substr(str, siz.start, siz.length), data);
	ft_strlen(str);
	ft_strlen(temp);
	tempfull = malloc((ft_strlen(str) - siz.length + ft_strlen(temp)));
	while (str[siz.i] != '\0')
	{
		if (str[siz.i] == '$')
		{
			while (temp[siz.j] != '\0')
			{
				tempfull[siz.i + siz.j] = temp[siz.j];
				siz.j++;
			}
			while (str[siz.i] != '\"' || str[siz.i] != '\'')
				siz.i++;
		}
		else
			tempfull[siz.i] = str[siz.i];
		siz.i++;
	}
	

	


	return (tempfull);
}

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
			j = size;
			while (data->environ[i][j] != '\0')
			{
				temp[j - size] = data->environ[i][j];
				j++;
			}
			temp[j - size] = '\0';
			return (temp);
		}
		i++;
	}
	return (NULL);
}

void	checker_looper(t_data *data)
{
	t_tok	*temp_t;
	t_cmds	*temp_c;
	char	*temp;

	temp_t = data->cmds->tokens;
	temp_c = data->cmds;
	while (temp_c != NULL)
	{
		temp_t = temp_c->tokens;
		while (temp_t != NULL)
		{
			temp_t->quote_type = check_quote_type_dollar(temp_t->content); // if error occurs returns with -1 (for later somwhere has to collect this)
			if (temp_t->quote_type == DOLLARQ)

			
			temp = temp_t->content;
			free(temp_t->content);
			temp_t->content = quote_cutter(temp, 0, 0);
			temp_t = temp_t->next;
		}
		temp_c = temp_c->next;






	}
}

void looper_next(t_data *data, void (*f)(char *))
{
	if (data->cmds == NULL)
	{
		printf("STOP HERE\n");
		return ;
	}
	while (data->cmds != NULL)
	{
		while (data->cmds->tokens != NULL)
		{
			(*f)(data->cmds->tokens->content);
			data->cmds->tokens = data->cmds->tokens->next;
		}
		data->cmds = data->cmds->next;
	}
}

void	commands_link_to_array_looper(t_data *data)
{
	t_tok	*temp_t;
	t_cmds	*temp_c;
	char	**temp;
	int		i;

	temp_t = data->cmds->tokens;
	temp_c = data->cmds;
	while (temp_c != NULL)
	{
		temp = malloc((temp_c->comandcount + 1) * sizeof(char*));
		temp_t = temp_c->tokens;
		i = 0;
		while (temp_t != NULL)
		{
			temp[i] = temp_t->content;
			temp_t = temp_t->next;
			i++;
		}
		temp[i] = NULL;
		temp_c->commands = temp;
		temp_c = temp_c->next;
		free(temp);
	}
}


