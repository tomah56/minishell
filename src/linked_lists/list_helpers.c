/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:12:51 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/25 21:23:57 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_tokens(t_data	*data)
{
	t_tok	*temp_t;
	t_cmds	*temp_c;
	int		i;

	i = 1;
	temp_t = data->cmds->tokens;
	temp_c = data->cmds;
	while (temp_t->next != NULL)
	{
		temp_t = temp_t->next;
		i++;
	}
	return (i);
}
