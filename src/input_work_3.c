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
	t_cmds	*temp_c;
	char	**temp;
	int i = 0;
	int j = 0;

	i = 0;
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
		free(temp);
		temp_c = temp_c->next;
		j++;
	}
}