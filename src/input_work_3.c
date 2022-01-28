#include "../include/minishell.h"


void quote_cutter_dollar(char *str)
{
	// int i;

	printf("%s\n", str);
	// i = 0;
	// while (str[i] != '\0')
	// {
	// 	i++;
	// }
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
	t_cmds *temp_c;
	int i = 1;
	int j = 1;

	i = 0;
	temp_t = data->cmds->tokens;
	temp_c = data->cmds;
	while (temp_c != NULL)
	{
		temp_t = temp_c->tokens;
		while (temp_t != NULL)
		{
			// if (((temp_t->content == '<' && temp_t->next->content != '<')) || temp_t->content == '>' && temp_t->next->content != '>' ))
			// printf("%s-->", temp_t->content);
			temp_t = temp_t->next;
			i++;
		}
		temp_c = temp_c->next;
		j++;
	}
}