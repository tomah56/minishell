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

void	ot_remove_node(t_tok **head, t_tok *node_to_remove)
{
	if (*head == NULL || node_to_remove == NULL)
	{

		printf("Hello X\n\n");
		return ;
	}

	if (*head == node_to_remove)
	{
		printf("Hello 1\n");
		*head = node_to_remove->next;
	}
 
	if (node_to_remove->prev != NULL)
	{
		

		printf("Hello 3\n");
		node_to_remove->prev->next = node_to_remove->next;

	}
	else if (node_to_remove->next == NULL)
	{
		printf("Hello 2\n");
		*head = NULL;
	}

	if (node_to_remove->next != NULL)
	{

		printf("Hello 4\n");
		node_to_remove->next->prev = node_to_remove->prev;
	}
	else
	{
		printf("Hello 5\n");
		// node_to_remove->next->prev = NULL;
	}

		printf("\n");

	// free(node_to_remove);
	return ;
}

void _temp_ot_remove_node(t_tok  **list, t_tok  *node)
{
	if (list == NULL || node == NULL)
		return ;

	if (node->prev == NULL)
	{
		if (node->next == NULL)
			*list = NULL;
		else
			node->next->prev = NULL;
	}
	node->prev->next = NULL;
	if (node->next)
		node->next->prev = node->prev;
	free(node->content);
	free(node);
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
	// free(node_to_remove->content);
	// node_to_remove->content = NULL;
	// free(node_to_remove);
	// ft_free_array((*head)->tokensfull);
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
	return ;
}
