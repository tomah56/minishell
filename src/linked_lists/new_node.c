/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:16:33 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/09 16:52:51 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmds	*create_new_cmds_node(t_tok *tokdat, int count)
{
	t_cmds	*list;

	list = ft_calloc(1, sizeof(t_cmds));
	if (list == NULL)
		return (NULL);
	list->tokens = tokdat;
	list->next = NULL;
	list->prev = NULL;
	list->commands = NULL;
	list->heredoc = -10;
	list->comandcount = count;
	return (list);
}

t_tok	*create_new_token_node(char *str)
{
	t_tok	*list;

	list = ft_calloc(1, sizeof(t_tok));
	if (list == NULL)
		return (NULL);
	list->next = NULL;
	list->prev = NULL;
	list->content = str;
	return (list);
}

void	remove_node(t_tok **head, t_tok *node_to_remove)
{
	if (*head == NULL || node_to_remove == NULL)
		return ;
	if (*head == node_to_remove)
	{
		*head = node_to_remove -> next;
		if (*head != NULL)
		{
			(*head)-> prev = NULL;
		}
		(*head)-> prev = NULL;
		free(node_to_remove);
		return ;
	}
	else
	{
		node_to_remove -> prev -> next = node_to_remove -> next;
		if (node_to_remove -> next != NULL)
		{
			node_to_remove -> next -> prev = node_to_remove -> prev;
		}
		node_to_remove -> next = NULL;
		node_to_remove -> prev = NULL;
	}
	free(node_to_remove);
	return ;
}

void	remove_node_c(t_cmds **head, t_cmds *node_to_remove)
{
	if (*head == NULL || node_to_remove == NULL)
		return ;
	if (*head == node_to_remove)
	{
		*head = node_to_remove -> next;
		if (*head != NULL)
		{
			(*head)-> prev = NULL;
		}
		(*head)-> prev = NULL;
		free(node_to_remove);
		return ;
	}
	else
	{
		node_to_remove -> prev -> next = node_to_remove -> next;
		if (node_to_remove -> next != NULL)
		{
			node_to_remove -> next -> prev = node_to_remove -> prev;
		}
		node_to_remove -> next = NULL;
		node_to_remove -> prev = NULL;
	}
	free(node_to_remove);
	return ;
}
