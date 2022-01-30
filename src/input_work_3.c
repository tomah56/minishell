#include "../include/minishell.h"

char	*quote_cutter(char *str, int qusig, int qudou)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	temp = malloc((ft_strlen(str) - 2) * sizeof(char));
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && qudou == 0)
			qusig = 1;
		else if (str[i] == '\"' && qusig == 0)
			qudou = 1;
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

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			return (QUDOUBLE);
		if (str[i] == '\'')
			return (QUSINGLE);
		i++;
	}
	return (NOQUOTE);
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


