/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_and_link_toaray.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 21:26:24 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/17 21:26:24 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static char *cut_path_off(char *srt, t_cmds	*temp_c, t_data *data)
{
	int i;
	int j;

	i = 0;
	temp_c->defpath = srt;
	while (*srt != '\0')
	{
		(srt)++;
		i++;
	}
	j = i;
	while (*srt != '/')
	{
		(srt)--;
		i--;
	}
	data->dpflag = 1;
	return (ft_substr(srt, 1, j - i));
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
		temp = malloc((temp_c->comandcount + 1) * sizeof(char *));
		printf("kiki %p\n", temp);
		temp_t = temp_c->tokens;
		i = 0;
		while (temp_t != NULL)
		{
			if (i == 0 && temp_t->content[0] == '/')
				temp[i] = cut_path_off(temp_t->content, temp_c, data);
			else
				temp[i] = temp_t->content;
			temp_t = temp_t->next;
			i++;
		}
		temp[i] = NULL;
		temp_c->commands = temp;
		temp_c = temp_c->next;
	}
}
