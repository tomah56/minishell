/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:16:33 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/24 16:42:07 by sreinhol         ###   ########.fr       */
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

t_tok	*create_new_token_node(t_data *data)
{
	t_tok	*list;

	list = ft_calloc(1, sizeof(t_tok));
	if (list == NULL)
		msg_exit(data, "malloc error");
	list->next = NULL;
	list->prev = NULL;
	list->content = NULL;
	return (list);
}
