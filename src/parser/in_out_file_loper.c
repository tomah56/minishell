/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_file_loper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:07:28 by sreinhol          #+#    #+#             */
/*   Updated: 2022/03/06 17:53:35 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_tok	*only_heredoc(t_data *data, t_cmds	*temp_c)
{
	t_tok	*temp_t;

	temp_t = NULL;
	if (count_commands(data) == 1)
	{
		data->falg = 0;
		free_struct_hd(data);
		return (NULL);
	}
	remove_node_c(&data->cmds, temp_c);
	return (temp_t);
}

static void	in_out_norm(t_tok **temp_t, t_cmds	*temp_c, t_data *data)
{
	t_tok	*temp_t2;

	if ((*temp_t)->bedeleted == 1)
	{
		temp_t2 = (*temp_t)->next->next;
		free((*temp_t)->content);
		*temp_t = (*temp_t)->next;
		free((*temp_t)->content);
		if (count_tokens(temp_c) == 2)
			*temp_t = only_heredoc(data, temp_c);
		else
		{
			remove_node(&temp_c->tokens, (*temp_t)->prev);
			remove_node(&temp_c->tokens, (*temp_t));
			*temp_t = temp_t2;
		}
	}
	else
		*temp_t = (*temp_t)->next;
}

void	remove_linklist_file_looper(t_data *data)
{
	t_tok	*temp_t;
	t_cmds	*temp_c;

	temp_c = data->cmds;
	temp_t = data->cmds->tokens;
	while (temp_c->next != NULL)
	{
		temp_c->last = false;
		temp_c = temp_c->next;
	}
	temp_c->last = true;
	temp_c = data->cmds;
	while (temp_c != NULL)
	{
		temp_t = temp_c->tokens;
		while (temp_t != NULL)
		{
			in_out_norm(&temp_t, temp_c, data);
		}
		temp_c = temp_c->next;
	}
}

static t_cmds	*in_out_helper(t_cmds **temp_c, t_tok **temp_t)
{
	while ((*temp_t) != NULL)
	{
		if ((*temp_t)->infile != -1)
		{
			if ((*temp_c)->infile != 0)
				close((*temp_c)->infile);
			(*temp_c)->infile = (*temp_t)->infile;
		}
		if ((*temp_t)->outfile != -1)
		{
			if ((*temp_c)->outfile != 1)
				close((*temp_c)->outfile);
			(*temp_c)->outfile = (*temp_t)->outfile;
		}
		if ((*temp_t)->hd_file != NULL)
		{
			unlink((*temp_c)->cm_hd_file);
			(*temp_c)->cm_hd_file = (*temp_t)->hd_file;
		}
		(*temp_t) = (*temp_t)->next;
	}
	return (*temp_c);
}

void	in_out_file_looper(t_data *data)
{
	t_tok	*temp_t;
	t_cmds	*temp_c;

	temp_c = data->cmds;
	temp_t = data->cmds->tokens;
	while (temp_c != NULL)
	{
		temp_t = temp_c->tokens;
		temp_c = in_out_helper(&temp_c, &temp_t);
		temp_c = temp_c->next;
	}
}
