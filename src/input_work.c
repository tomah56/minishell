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


#include "../include/minishell.h"

static void check_token_flags(char str, t_tok *tokdat)
{
	if (str == '"' && tokdat->qudouble == 0 && tokdat->qusingle == 0)
		tokdat->qudouble = 1;
	else if (str == '"' && tokdat->qudouble == 1 && tokdat->qusingle == 0)
		tokdat->qudouble = 0;
	if (str == '\'' && tokdat->qusingle == 0 && tokdat->qudouble == 0)
		tokdat->qusingle = 1;
	else if (str == '\'' && tokdat->qusingle == 1 && tokdat->qudouble == 0)
		tokdat->qusingle = 0;
}
static void check_token_flags_li(char str, t_data *data)
{
	if (str == '"' && data->qudouble == 0 && data->qusingle == 0)
		data->qudouble = 1;
	else if (str == '"' && data->qudouble == 1 && data->qusingle == 0)
		data->qudouble = 0;
	if (str == '\'' && data->qusingle == 0 && data->qudouble == 0)
		data->qusingle = 1;
	else if (str == '\'' && data->qusingle == 1 && data->qudouble == 0)
		data->qusingle = 0;
}

static int count_my_tokens(char *str, t_tok *tokdat, int i, int j)
{
	int count;

	count = 0;
	while (str[i])
	{
		check_token_flags(str[i], tokdat);
		if (ft_strchr(" $<>|\0", str[i + 1]) != NULL && tokdat->qusingle == 0
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

// int token_separator(t_data *data)
// {
// 	char **alltoken;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	alltoken = data->cmds->tokens->tokensfull;
// 	while (alltoken[i] != NULL)
// 	{
// 		j = 0;
// 		while (alltoken[i][j] != '\0')
// 		{
// 			if (alltoken[i][j] == '$')
// 			{
				
// 			}
// 			j++;
// 		}
// 		i++;
// 	}

// }

int	input_one_array(char *str, t_tok *tokdat, int i, int j)
{
	int	k;

	k = -1;
	tokdat->tokencount = count_my_tokens(str, tokdat, 0, 0);
	tokdat->tokensfull = malloc((tokdat->tokencount + 2) * sizeof(char *)); // version array
	if (tokdat->tokensfull == NULL)
		return (0);
	while (str[i])
	{
		check_token_flags(str[i], tokdat);
		if (ft_strchr(" $<>|\0", str[i + 1]) != NULL && tokdat->qusingle == 0
			&& tokdat->qudouble == 0 )
		{
			tokdat->tokensfull[++k] = ft_substr(str, j, i + 1 - j); //save the tokens acordingly

			while (str[i + 1] == ' ')
				i++;
			j = i + 1;
		}
		i++;
	}
	tokdat->tokensfull[++k] = NULL;
	input_two(tokdat);
	return (1);
}





void	input_one_lilist_norm_cut(char *str, t_data *data)
{
	if (ft_strchr(" $<>|\0", str[data->i + 1]) != NULL && data->qusingle == 0
			&& data->qudouble == 0 )
	{
		add_token_node_at_back(&data->normtok, create_new_token_node(
				ft_substr(str, data->j, data->i + 1 - data->j)));
		while (str[data->i + 1] == ' ')
			(data->i)++;
		data->j = data->i + 1;
	}
	if (str[data->i + 1] == '|')
	{
		add_cmds_node_at_back(&data->normcm, 
			create_new_cmds_node(data->normtok));
		data->normtok = NULL;
	}
}

int	input_one_lilist(char *str, t_data *data, int k, int p)
{
	data->normcm = NULL;
	data->normtok = NULL;
	while (str[data->i])
	{
		check_token_flags_li(str[data->i], data);
		input_one_lilist_norm_cut(str, data);
		// if (ft_strchr(" $<>|\0", str[i + 1]) != NULL && data->qusingle == 0
		// 	&& data->qudouble == 0 )
		// {
		// 	add_token_node_at_back(&tok, create_new_token_node(ft_substr(str, j, i + 1 - j)));
		// 	while (str[i + 1] == ' ')
		// 		i++;
		// 	j = i + 1;
		// }
		// if (str[i + 1] == '|')
		// {
		// 	add_cmds_node_at_back(&cmds, create_new_cmds_node(tok));
		// 	tok = NULL;
		// }
		(data->i)++;
	}
	add_cmds_node_at_back(&data->normcm, create_new_cmds_node(data->normtok));
	data->cmds = data->normcm;
	return (1);
}
