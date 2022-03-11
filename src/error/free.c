/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:49:12 by sreinhol          #+#    #+#             */
/*   Updated: 2022/03/09 17:29:35 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_struct_hd(t_data *data)
{
	if (data->paths != NULL)
		ft_free_array(data->paths);
	if (data->cmds != NULL)
	{
		unlink(data->cmds->cm_hd_file);
		while (data->cmds->tokens != NULL)
		{
			free(data->cmds->tokens);
			data->cmds->tokens = data->cmds->tokens->next;
		}
		if (data->cmds->commands != NULL)
		{
			ft_free_array(data->cmds->commands);
		}
		free(data->cmds->defpath);
		free(data->cmds);
	}
	data->paths = NULL;
	data->actual = NULL;
}

int	free_struct(t_data *data)
{
	if (data->paths != NULL)
		ft_free_array(data->paths);
	while (data->cmds && data != NULL && data->tokentotal != 0)
	{
		if (data->cmds != NULL)
		{
			unlink(data->cmds->cm_hd_file);
			free(data->cmds->cm_hd_file);
			while (data->cmds->tokens != NULL)
			{
				free(data->cmds->tokens);
				data->cmds->tokens = data->cmds->tokens->next;
			}
			if (data->cmds != NULL && data->cmds->commands != NULL)
				ft_free_array(data->cmds->commands);
			free(data->cmds->defpath);
			free(data->cmds);
			data->cmds = data->cmds->next;
		}
	}
	data->paths = NULL;
	data->cmds = NULL;
	data->actual = NULL;
	return (1);
}

int	free_struct_sig(t_data *data)
{
	if (data->paths != NULL)
		ft_free_array(data->paths);
	while (data->cmds && data != NULL && data->tokentotal != 0)
	{
		if (data->cmds != NULL)
		{
			unlink(data->cmds->cm_hd_file);
			while (data->cmds->tokens != NULL)
			{
				free(data->cmds->tokens->content);
				free(data->cmds->tokens);
				data->cmds->tokens = data->cmds->tokens->next;
			}
			if (data->cmds->commands != NULL)
				ft_free_array(data->cmds->commands);
			free(data->cmds->defpath);
			free(data->cmds);
			data->cmds = data->cmds->next;
		}
	}
	data->paths = NULL;
	data->cmds = NULL;
	data->actual = NULL;
	return (1);
}

void	ft_free_3array(char ***input)
{
	int	i;

	i = 0;
	if (input == NULL || *input == NULL)
		return ;
	while ((*input)[i] != NULL)
	{
		if (*((*input)[i]) != 0)
			free((*input)[i]);
		(*input)[i] = NULL;
		i++;
	}
	free(*input);
	*input = NULL;
}

void	ft_free_2array(void **to_free)
{
	if (*to_free == NULL)
		return ;
	free(*to_free);
	*to_free = NULL;
}
