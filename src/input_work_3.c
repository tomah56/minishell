#include "../include/minishell.h"


char	*quote_cutter(char *str)
{
	int		i;
	int		j;
	char	*temp;
	int qusig;
	int qudou;

	qusig = 0;
	qudou = 0;
	i = 0;
	j = 0;
	temp = malloc((ft_strlen(str) - 2) * sizeof(char));
	while (str[i] != '\0')
	{
		if (!(str[i] == '\'' || qudou == 1) || !(str[i] == '\"' || qusig == 1))
		{
			temp[j] = str[i];
			j++;
		}
			// if (str[i] != '\'' && qudou == 0)
			// 	qusig = 1;
			// if (str[i] != '\"' && qusig == 0)
			// 	qudou = 1;
		i++;
	}
	temp[j] = '\0';
	return (temp);
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

void	temp_looper(t_data *data)
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
