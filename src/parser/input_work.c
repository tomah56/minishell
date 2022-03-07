/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:30:55 by ttokesi           #+#    #+#             */
/*   Updated: 2022/01/24 23:06:22 by ttokesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_my_tokens(char *str, t_tok *tokdat, int i, int j)
{
	int	count;

	count = 0;
	while (str[i])
	{
		if (ft_strchr(" <>|\0", str[i + 1]) != NULL && tokdat->qusingle == 0
			&& tokdat->qudouble == 0)
		{
			while (str[i + 1] == ' ')
				i++;
			j = i + 1;
			count++;
		}
		i++;
	}
	tokdat->qudouble = 0;
	tokdat->qusingle = 0;
	return (count);
}

int	is_double(char str, char strp1)
{
	if ((str == '<' || str == '>') && str == strp1)
	{
		return (1);
	}
	return (0);
}

void	inp_o_li_norm_cut(char *str, t_data *data, t_cmds **cmds, t_tok **tok)
{
	if ((ft_strchr(" <>|\0", str[data->i + 1]) != NULL
			|| ft_strchr("<>|", str[data->i])
			!= NULL) && data->qusingle == 0 && data->qudouble == 0)
	{
		while ((data->j) == 0 && str[(data->j)] == ' ')
			(data->j)++;
		if (is_double(str[data->i], str[data->i + 1]))
			(data->i)++;
		if (data->i + 1 - data->j != 0 && str[(data->i)] != '|')
			add_token_node_at_back(tok, create_new_token_node(
					ft_substr(str, data->j, data->i + 1 - data->j)));
		while (str[data->i + 1] == ' ')
			(data->i)++;
		data->j = (data->i) + 1;
		(data->tokentotal)++;
		(data->tokencount)++;
	}
	if (str[(data->i) + 1] == '|')
	{
		add_cmds_node_at_back(cmds, create_new_cmds_node
			(*tok, data->tokencount));
		*tok = NULL;
		data->tokencount = 0;
	}
}

static int	cut_first_pipie(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '	')
		i++;
	if (str[i] == '|')
	{
		write(STDERR_FILENO, "syntax error near unexpected token `|'\n", 39);
		g_exit = 258;
		return (1);
	}
	return (0);
}

int	input_one_lilist(char *str, t_data *data)
{
	t_cmds	*cmds;
	t_tok	*tok;

	cmds = NULL;
	tok = NULL;
	data->tokentotal = 0;
	data->tokencount = 0;
	if (cut_first_pipie(str))
		return (1);
	while (str[data->i])
	{
		check_token_flags_li(str[data->i], data);
		inp_o_li_norm_cut(str, data, &cmds, &tok);
		(data->i)++;
	}
	add_cmds_node_at_back(&cmds, create_new_cmds_node(tok, data->tokencount));
	if (data->qudouble == 1 || data->qusingle == 1)
		write(1, "error: input\n", 13);
	data->cmds = cmds;
	return (0);
}
