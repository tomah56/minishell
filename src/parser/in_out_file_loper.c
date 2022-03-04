/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_file_loper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:07:28 by sreinhol          #+#    #+#             */
/*   Updated: 2022/03/04 20:20:00 by sreinhol         ###   ########.fr       */
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
		return (NULL); // possible segfoults when dlete in the end.
	}
	remove_node_c(&data->cmds, temp_c);
	return (temp_t);
}

// it fails in these cases.. Why???

// HAKUNA MATATA 0.42$ >ju.txt | < juk jsj | < why.txt 
// CMDS 1  number of tokens: 1
// jsj[---]
// jsj
// HAKUNA MATATA 0.42$ >ju.txt | < juk jsj | < why.txt  | >bik.txt
// CMDS 1  number of tokens: 1
// jsj[---]
// CMDS 2  number of tokens: 2
// >[---]bik.txt[---]
// jsj
// >
// bik.txt

static void	in_out_norm(t_tok **temp_t, t_cmds	*temp_c, t_data *data)
{
	t_tok	*temp_t2;

	if ((*temp_t)->bedeleted == 1)
	{
		temp_t2 = (*temp_t)->next->next;
		*temp_t = (*temp_t)->next;
		if (count_tokens(temp_c) == 2)
			*temp_t = only_heredoc(data, temp_c);
		else
		{
			remove_node(&temp_c->tokens, (*temp_t)->prev); // freeeing content is not working... is it a leak???
			remove_node(&temp_c->tokens, (*temp_t));
			*temp_t = temp_t2;
		}
	}
	else
		*temp_t = (*temp_t)->next;
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
		while (temp_t != NULL)
		{
			if (temp_t->infile != -1)
			{
				if (temp_c->infile != 0)
					close(temp_c->infile);
				temp_c->infile = temp_t->infile;
			}
			if (temp_t->outfile != -1)
			{
				if (temp_c->outfile != 1)
					close(temp_c->outfile);
				temp_c->outfile = temp_t->outfile;
			}
			if (temp_t->hd_file != NULL)
			{
				unlink(temp_c->cm_hd_file);
				temp_c->cm_hd_file = temp_t->hd_file;
			}
			temp_t = temp_t->next;
		}
		temp_c = temp_c->next;
	}
}

void	remove_linklist_file_looper(t_data *data)
{
	t_tok	*temp_t;
	t_cmds	*temp_c;

	temp_c = data->cmds;
	temp_t = data->cmds->tokens;
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
