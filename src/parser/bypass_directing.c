/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bypass_directing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 21:06:37 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/17 21:06:37 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static void check_next_syntax()

static int short_tre(t_tok **temp_t)
{
	(*temp_t)->bedeleted = 1;
	*temp_t = (*temp_t)->next;
	if (syntax_rutine(temp_t) == -1)
		return (-1);
	(*temp_t)->bedeleted = 1;
	return (0);
}

int	bypass_helper(t_tok **temp_t, t_cmds *temp_c, t_data *data, int fail)
{
	temp_c->outfile = -5;
	temp_c->infile = -5;
	if (!ft_strncmp((*temp_t)->content, ">", 2))
	{
		fail = short_tre(temp_t);
		if (fail == 0)
			fail = red_outfile_trunc(data, temp_c, temp_t);
	}
	else if (!ft_strncmp((*temp_t)->content, "<", 2))
	{
		fail = short_tre(temp_t);
		if (fail == 0)
			fail = red_infile(data, temp_c, temp_t);
	}
	else if (!ft_strncmp((*temp_t)->content, ">>", 3))
	{
		fail = short_tre(temp_t);
		if (fail == 0)
			fail = red_outfile_append(data, temp_c, temp_t);
	}
	if (fail == -1)
	{
		return (-1);
	}
	*temp_t = (*temp_t)->next;
	return (fail);
}

int	bypass_juntion(t_data *data)
{
	t_tok	*temp_t;
	t_cmds	*temp_c;
	int		fail;

	fail = 0;
	temp_t = data->cmds->tokens;
	temp_c = data->cmds;
	temp_c->fail = 0;
	while (temp_c != NULL)
	{
		temp_t = temp_c->tokens;
		temp_c->type = 0;
		while (temp_t != NULL && fail != -1)
		{
			fail = bypass_helper(&temp_t, temp_c, data, fail);
			if (fail == 1)
				temp_c->fail = 1;
		}
		if (temp_c->next != NULL)
			temp_c->type = PIPE;
		if (fail == 0)
			temp_c = temp_c->next;
		else
			return (1);
	}
	return (0);
}
