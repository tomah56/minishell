/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 01:31:15 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/25 20:14:21 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmds	*cmds_lstlast(t_cmds *lst)
{
	t_cmds	*last;

	last = lst;
	while (lst != NULL)
	{
		last = lst;
		lst = last->next;
	}
	return (last);
}

void	add_cmds_node_at_back(t_cmds **list, t_cmds *newnode)
{
	t_cmds	*last;

	if (!newnode)
		return ;
	newnode->next = NULL;
	last = cmds_lstlast(*list);
	if (!list || !(*list))
	{
		*list = newnode;
		newnode->next = NULL;
		newnode->prev = NULL;
	}
	else if (list && newnode)
	{
		newnode->next = NULL;
		last->next = newnode;
		newnode->prev = last;
	}
}

t_tok	*inster_at_head(t_tok **head, t_tok *node_to_insert)
{
	node_to_insert -> next = *head;
	if (*head != NULL)
		(*head)-> prev = node_to_insert;
	*head = node_to_insert;
	node_to_insert -> prev = NULL;
	return (node_to_insert);
}

t_tok	*tok_lstlast(t_tok *lst)
{
	t_tok	*last;

	last = lst;
	while (lst != NULL)
	{
		last = lst;
		lst = last->next;
	}
	return (last);
}

void	add_token_node_at_back(t_tok **list, t_tok *newnode)
{
	t_tok	*last;

	if (!newnode)
		return ;
	newnode->next = NULL;
	last = tok_lstlast(*list);
	if (!list || !(*list))
	{
		*list = newnode;
		newnode->next = NULL;
		newnode->prev = NULL;
	}
	else if (list && newnode)
	{
		newnode->next = NULL;
		last->next = newnode;
		newnode->prev = last;
	}
}


