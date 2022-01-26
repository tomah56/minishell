/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:12:51 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/26 17:19:17 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_tokens(t_cmds	*actual)
{
	t_tok	*temp_t;
	int		i;

	i = 1;
	temp_t = actual->tokens;
	while (temp_t->next != NULL)
	{
		temp_t = temp_t->next;
		i++;
	}
	return (i);
}
