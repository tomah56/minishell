/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:11:03 by sreinhol          #+#    #+#             */
/*   Updated: 2022/03/07 17:12:47 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sytax_looper(t_data *data)
{
	t_tok	*temp_t;
	t_cmds	*temp_c;

	temp_t = data->cmds->tokens;
	temp_c = data->cmds;
	data->dpflag = 0;
	while (temp_c != NULL)
	{
		temp_t = temp_c->tokens;
		// temp_c->defpath = ft_strjoin("./", temp_c->commands[0]); // not in the rigth place...  // version for inside the place
		temp_c->defpath = NULL;
		temp_c = temp_c->next;
	}
}

int	syntax_rutine(t_tok **temp_t)
{
	if ((*temp_t) && (*temp_t)->content
		&& ft_strchr("<>", (*temp_t)->content[0]))
	{
		write(STDERR_FILENO, "syntax error near unexpected token `", 36);
		write(STDERR_FILENO, &(*temp_t)->content[0], 1);
		write(STDERR_FILENO, "'\n", 2);
		g_exit = 258;
		return (-1);
	}
	if (!(*temp_t))
	{
		write(STDERR_FILENO, "syntax error near unexpected token\n", 35);
		g_exit = 258;
		return (-1);
	}
	return (0);
}
