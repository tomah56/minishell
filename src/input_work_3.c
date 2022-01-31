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
	size.len = 0;
	size.i = 0;
	size.j = 0;
	size.sta = 0;
	size.ori = ft_strlen(str);
	while (str[i] !='\0')
	{
		if (size.len != 0 && !ft_isalnum(str[i]))
			break ;
		if (str[i] == '$' || size.len != 0)
			size.len++;
		if (str[i] == '$')
			size.sta = i;
		i++;
	}
	return (size);
}



char *expand_dirt_dollar(char *str, t_data *data)
{
	char *doll;
	char *jo1;
	char *allof;
	int new;
	t_s siz;
	// while

	//siz = size_dollar(str + siz.start + siz.len); 
	allof = NULL;
	siz = size_dollar(str);
	while (siz.ori != 0)
	{
		if (siz.len == 0)
		{
			jo1 = ft_strdup(str + new);
			siz.ori = 0;
		}
		else
		{

			doll = expand_clean_dollar(ft_substr(str, siz.sta, siz.len), data);
			new = ft_strlen(doll);
			jo1 = malloc((siz.sta + new) + 1);
			while (siz.i < siz.sta + new)
			{
				if (str[siz.i] == '$')
				{
					while (doll[siz.j] != '\0')
					{
						jo1[siz.i + siz.j] = doll[siz.j];
						siz.j++;
					}
				}
				else if (siz.i < siz.sta)
					jo1[siz.i] = str[siz.i];
				siz.i++;
			}
			jo1[siz.sta + new] = '\0';
			new = siz.sta + siz.len;
			siz = size_dollar(str + siz.sta + siz.len);
			printf("ori: %d   sta: %d   len: %d\n", siz.ori, siz.sta, siz.len);
		}
		if (allof == NULL)
			allof = ft_strdup(jo1);
		else
			allof = ft_strjoin(allof, jo1);
	}

	// printf("%s\n", jo1);


	return (allof);
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


