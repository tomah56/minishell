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

int	bypass_helper(t_tok **temp_t, t_cmds *temp_c, t_data *data, int fail)
{
	temp_c->outfile = -5;
	temp_c->infile = -5;
	if (!ft_strncmp((*temp_t)->content, ">", 2))
	{
		(*temp_t)->bedeleted = 1;
		*temp_t = (*temp_t)->next;
		(*temp_t)->bedeleted = 1;
		fail = red_outfile_trunc(data, temp_c, temp_t);
	}
	else if (!ft_strncmp((*temp_t)->content, "<", 2))
	{
		(*temp_t)->bedeleted = 1;
		*temp_t = (*temp_t)->next;
		(*temp_t)->bedeleted = 1;
		fail = red_infile(data, temp_c, temp_t);
	}
	else if (!ft_strncmp((*temp_t)->content, ">>", 3))
	{
		(*temp_t)->bedeleted = 1;
		*temp_t = (*temp_t)->next;
		(*temp_t)->bedeleted = 1;
		fail = red_outfile_append(data, temp_c, temp_t);
	}
	*temp_t = (*temp_t)->next;
	return (fail);
}

void	bypass_juntion(t_data *data)
{
	t_tok	*temp_t;
	t_cmds	*temp_c;
	int		fail;

	fail = 0;
	temp_t = data->cmds->tokens;
	temp_c = data->cmds;
	while (temp_c != NULL)
	{
		temp_t = temp_c->tokens;
		while (temp_t != NULL)
		{
			fail = bypass_helper(&temp_t, temp_c, data, fail);
		}
		if (temp_c->next != NULL)
			temp_c->type = PIPE;
		if (fail == 0)
			temp_c = temp_c->next;
		else
			break ;
	}
}

// static int	file_opener(char *filtogo, t_data *data)
// {
// 	char	*temp;
// 	int		size;
// 	int		fd;

// 	// close(fd); // when we loop over to find the latest one we close the previous ones
// 	if (filtogo == NULL)
// 	{
// 		write(2, "ERROR\n", 6);
// 		return (-1); // bash: syntax error near unexpected token `newline'
// 	}
// 	fd = open(filtogo, O_WRONLY | O_CREAT | O_APPEND, 0777); //which mode do we need? 0644
// 	if (fd == FAILED)
// 	{
// 		write(2, "ERROR\n", 6); // temperarrly
// 		return (-1);
// 	}
// 	return (fd);
// }

// static void	by_pa_norm(t_tok **temp_t, t_cmds	*temp_c, t_data *data)
// {
// 	t_tok	*temp_t2;

// 	if (!ft_strncmp((*temp_t)->content, ">", 2))
// 	{
// 		(*temp_t)->bedeleted = 1;
// 		*temp_t = (*temp_t)->next;
// 		(*temp_t)->bedeleted = 1;
// 		(*temp_t)->outfile = file_opener((*temp_t)->content, data);
// 	}
// 	else if (!ft_strncmp((*temp_t)->content, "<", 2))
// 	{
// 		(*temp_t)->bedeleted = 1;
// 		*temp_t = (*temp_t)->next;
// 		(*temp_t)->bedeleted = 1;
// 		(*temp_t)->infile = file_opener((*temp_t)->content, data);
// 	}
// 	*temp_t = (*temp_t)->next;
// }

// void	bypass_juntion(t_data *data)
// {
// 	t_tok	*temp_t;
// 	t_cmds	*temp_c;

// 	temp_t = data->cmds->tokens;
// 	temp_c = data->cmds;
// 	while (temp_c != NULL)
// 	{
// 		temp_t = temp_c->tokens;
// 		while (temp_t != NULL)
// 		{
// 			by_pa_norm(&temp_t, temp_c, data);
// 		}
// 		temp_c = temp_c->next;
// 	}
// }




// static void with_delete_by_pa_norm(t_tok **temp_t, t_cmds	*temp_c, t_data *data)
// {
// 	if (!ft_strncmp((*temp_t)->content, ">", 1))
// 	{
// 		temp_t2 = (*temp_t)->next->next;
// 		*temp_t = (*temp_t)->next;
// 		(*temp_t)->outfile = file_opener((*temp_t)->content, data);
// 		if (count_tokens(temp_c) == 2)
// 			*temp_t = only_heredoc(data, temp_c);
// 		else
// 		{
// 			remove_node(&temp_c->tokens, (*temp_t)->prev); // freeeing content is not working... is it a leak???
// 			remove_node(&temp_c->tokens, (*temp_t));
// 			*temp_t = temp_t2;
// 		}
// 	}
// 	else if (!ft_strncmp((*temp_t)->content, "<", 1))
// 	{
// 		temp_t2 = (*temp_t)->next->next;
// 		*temp_t = (*temp_t)->next;
// 		(*temp_t)->infile = file_opener((*temp_t)->content, data);
// 		if (count_tokens(temp_c) == 2)
// 			*temp_t = only_heredoc(data, temp_c);
// 		else
// 		{
// 			remove_node(&temp_c->tokens, (*temp_t)->prev); // freeeing content is not working... is it a leak???
// 			remove_node(&temp_c->tokens, (*temp_t));
// 			*temp_t = temp_t2;
// 		}
// 	}
// 	else
// 		*temp_t = (*temp_t)->next;
// }

// void	bypass_juntion(t_data *data)
// {
// 	t_tok	*temp_t;
// 	t_cmds	*temp_c;

// 	temp_t = data->cmds->tokens;
// 	temp_c = data->cmds;
// 	data->dpflag = 0;
// 	while (temp_c != NULL)
// 	{
// 		temp_t = temp_c->tokens;
// 		temp_c->defpath = NULL;
// 		while (temp_t != NULL)
// 		{
// 			by_pa_norm(&temp_t, temp_c, data);
// 		}
// 		temp_c = temp_c->next;
// 	}
// }
// }
