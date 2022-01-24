/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:16:33 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/24 16:58:54 by ttokesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

t_cmds	*create_new_cmds_node(t_data *data)
{
	t_cmds	*list;

	list = ft_calloc(1, sizeof(t_cmds));
	if (list == NULL)
		msg_exit(data, "malloc error");
	list->next = NULL;
	list->prev = NULL;
	list->infile = STDIN_FILENO;
	list->outfile = STDOUT_FILENO;
	list->commands = NULL;
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
