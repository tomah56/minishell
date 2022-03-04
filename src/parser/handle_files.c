/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:31:08 by sreinhol          #+#    #+#             */
/*   Updated: 2022/03/02 22:09:05 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	red_outfile_trunc(t_data *data, t_cmds *temp_c, t_tok **temp_t)
{
	int	fail;

	fail = 0;
	temp_c->type = RED_OUT_TRUNC;
	if ((*temp_t)->outfile != -1)
		close((*temp_t)->outfile);
	(*temp_t)->outfile = open((*temp_t)->content, O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	if ((*temp_t)->outfile == FAILED)
	{
		error_msg((*temp_t)->content);
		fail = 1;
		g_exit = 1;
	}
	return (fail);
}

int	red_outfile_append(t_data *data, t_cmds *temp_c, t_tok **temp_t)
{
	int	fail;

	fail = 0;
	temp_c->type = RED_OUT_APPEND;
	if ((*temp_t)->outfile != -1)
		close((*temp_t)->outfile);
	(*temp_t)->outfile = open((*temp_t)->content, O_WRONLY | O_CREAT
			| O_APPEND, 0644);
	if ((*temp_t)->outfile == FAILED)
	{
		error_msg((*temp_t)->content);
		fail = 1;
		g_exit = 1;
	}
	return (fail);
}

int	red_infile(t_data *data, t_cmds *temp_c, t_tok **temp_t)
{
	int	fail;

	fail = 0;
	temp_c->type = RED_IN;
	if (access((*temp_t)->content, F_OK) != SUCCESS)
	{
		error_msg((*temp_t)->content);
		fail = 1;
		g_exit = 1;
	}
	if (temp_c->next == NULL && fail == 0)
	{
		if ((*temp_t)->infile != -1)
			close((*temp_t)->infile);
		(*temp_t)->infile = open((*temp_t)->content, O_RDONLY);
		if ((*temp_t)->infile == FAILED)
		{
			error_msg((*temp_t)->content);
			g_exit = 1;
		}
	}
	return (fail);
}
