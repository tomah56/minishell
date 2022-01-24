/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 01:31:15 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/24 03:14:39 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_cmds_node_at_back(t_cmds **list, t_cmds *newnode)
{
	t_cmds	*last;

	if (!newnode)
		return ;
	newnode->next = NULL;
	last = *list;
	while (last->next != NULL)
		last = last->next;
	newnode->prev = last;
}

void	add_token_node_at_back(t_tok **list, t_tok *newnode)
{
	t_tok	*last;

	if (!newnode)
		return ;
	newnode->next = NULL;
	last = *list;
	while (last->next != NULL)
		last = last->next;
	newnode->prev = last;
}
