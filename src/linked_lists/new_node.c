/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:16:33 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/24 22:08:15 by ttokesi          ###   ########.fr       */
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
	list->infile = STDIN_FILENO;
	list->outfile = STDOUT_FILENO;
	list->commands = NULL;
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
	if (*head == node_to_remove)
	{
		*head = node_to_remove -> next;
		if (*head != NULL)
		{
			(*head) -> prev = NULL;
		}
		(*head) -> prev = NULL;
		return;
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
		//find prev node in list
		// node_t *temp = *head;
		// while (temp != NULL && temp -> next != node_to_remove)
		// {
		// 	temp = temp -> next;
		// }
		// if (temp == NULL)
		// 	return;
		// temp -> next = node_to_remove -> next;
		// node_to_remove -> next = NULL;
	}
	return;
}
