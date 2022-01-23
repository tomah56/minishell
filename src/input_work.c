/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:30:55 by ttokesi           #+#    #+#             */
/*   Updated: 2022/01/23 22:45:10 by ttokesi          ###   ########.fr       */
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

int	input_one(char *str, t_tok *tokdat, int i, int j)
{
	int	k;

	k = -1;
	tokdat->tokencount = count_my_tokens(str, tokdat, 0, 0);
	tokdat->tokensfull = malloc((tokdat->tokencount + 2) * sizeof(char *));
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
	// input_two(tokdat);
	return (1);
}
