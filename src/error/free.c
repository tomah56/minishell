/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:49:12 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/27 23:33:25 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_struct(t_data *data)
{
	if (data != NULL)
	{
		if (data->paths != NULL)
			ft_free_array(data->paths);
		if (data->cmds != NULL)
			free_cmds_struct(&data->cmds);
	}
	data->paths = NULL;
	data->cmds = NULL;
	data->actual = NULL;
}

void	free_cmds_struct(t_cmds **cmds)
{
	t_cmds	*temp_c;

	while (*cmds)
	{
		temp_c = *cmds;
		unlink(temp_c->cm_hd_file);
		*cmds = (*cmds)->next; // why stepping imidiatly in to the next one is working?
		if (temp_c->tokens != NULL)
			free_token_struct(&(temp_c->tokens));
		if (temp_c->commands != NULL)
			ft_free_array(temp_c->commands);
	}
	temp_c->commands = NULL;
}

void	free_token_struct(t_tok **token)
{
	t_tok	*temp_t;

	while (*token)
	{
		temp_t = *token;
		*token = (*token)->next;
		if (temp_t->tokensfull != NULL)
			ft_free_array(temp_t->tokensfull);
	}
	temp_t->tokensfull = NULL;
}

void	ft_free_3array(char ***input)
{
	int	i;

	i = 0;
	if (input == NULL || *input == NULL)
		return ;
	while ((*input)[i] != NULL)
	{
		free((*input)[i]);
		(*input)[i] = NULL;
		i++;
	}
	free(*input);
	*input = NULL;
}

void	ft_free_2array(void **to_free)
{
	if (*to_free == NULL)
		return ;
	free(*to_free);
	*to_free = NULL;
}
