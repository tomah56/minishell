/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:02:34 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/11 13:44:17 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	msg_exit(t_data *data, char *msg)
{
	free_struct(data);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void	free_struct(t_data *data)
{
	if (data != NULL)
	{
		if (data->paths != NULL)
			ft_free_array(data->paths);
		if (data->cmds != NULL)
			free_cmds_struct(&data->cmds);
	}
	data->paths = NULL;
	data->cmds = NULL;
	data->actual = NULL;
}

void	free_cmds_struct(t_cmds **cmds)
{
	t_cmds	*temp_c;

	while (*cmds)
	{
		temp_c = *cmds;
		*cmds = (*cmds)->next;
		if (temp_c->tokens != NULL)
			free_token_struct(&(temp_c->tokens));
		if (temp_c->commands != NULL)
			ft_free_array(temp_c->commands);
	}
	temp_c->commands = NULL;
}

void	free_token_struct(t_tok **token)
{
	t_tok	*temp_t;

	while (*token)
	{
		temp_t = *token;
		*token = (*token)->next;
		if (temp_t->tokensfull != NULL)
			ft_free_array(temp_t->tokensfull);
	}
	temp_t->tokensfull = NULL;
}

void	ft_free_3array(char ***input)
{
	int	i;

	i = 0;
	if (input == NULL || *input == NULL)
		return ;
	while ((*input)[i] != NULL)
	{
		free((*input)[i]);
		(*input)[i] = NULL;
		i++;
	}
	free(*input);
	*input = NULL;
}
