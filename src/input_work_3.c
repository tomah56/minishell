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
	// free(str);
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

// int check_quote_type_dollar(char *str)
// {
// 	int	i;
// 	int temp;

// 	i = 0;
// 	temp = 0;
// 	if (str == NULL)
// 		return (-1);
// 	while (str[i] != '\0')
// 	{
// 		if (temp == 0 && str[i] == '\"')
// 			temp = QUDOUBLE;
// 		else if (temp == 0 && str[i] == '\'')
// 			return (QUSINGLE);
// 		else if (temp == QUDOUBLE && str[i] == '$')
// 			return (DOLLARQ);
// 		else if (temp == QUDOUBLE && str[i] == '\"')
// 			return (temp);
// 		i++;
// 	}
// 	return (temp);
// }

// t_s size_dollar(char *str)
// {
// 	t_s size;
// 	int i;

// 	i = 0;
// 	size.len = 0;
// 	size.i = 0;
// 	size.j = 0;
// 	size.sta = 0;
// 	size.ori = ft_strlen(str);
// 	while (str[i] !='\0')
// 	{
// 		if (size.len != 0 && !ft_isalnum(str[i]))
// 			break ;
// 		if (str[i] == '$' || size.len != 0)
// 			size.len++;
// 		if (str[i] == '$')
// 			size.sta = i;
// 		i++;
// 	}
// 	return (size);
// }
