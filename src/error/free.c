/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:49:12 by sreinhol          #+#    #+#             */
/*   Updated: 2022/03/06 18:51:21 by sreinhol         ###   ########.fr       */
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
		// printf( "--1--  %p\n",data->cmds->cm_hd_file);
		// if (data->cmds->cm_hd_file != NULL)
		// free(data->cmds->cm_hd_file);
		while (data->cmds->tokens != NULL)
		{
		// printf( "--2--  %p\n",data->cmds->tokens);
		// printf("one\n");
			free(data->cmds->tokens);
			data->cmds->tokens = data->cmds->tokens->next;
		}
		if (data->cmds->commands != NULL)
		{
			printf("one\n");

			ft_free_array(data->cmds->commands);
		}
			// ft_free_array(data->cmds->commands);
	
		free(data->cmds->defpath);
		printf("one\n");
		free(data->cmds);
		
	}
	// free(data->cmds);
	data->paths = NULL;
	data->actual = NULL;
}
void	free_struct(t_data *data)
{
		printf("one S\n");
		if (data->paths != NULL)
			ft_free_array(data->paths);
		while (data->cmds && data != NULL && data->tokentotal != 0)
		{
			if (data->cmds != NULL)
			{


			// hello
				unlink(data->cmds->cm_hd_file);
				// if (data->cmds->cm_hd_file != NULL)  //antileaks in << he cat case
				// 	free(data->cmds->cm_hd_file);
				while (data->cmds->tokens != NULL)
				{
					printf("toke 0\n");
					// t_tok *temp;
					// temp = data->cmds->tokens;
					free(data->cmds->tokens);
					// data->cmds->tokens = temp->next;
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

void	ft_free_2array(void **to_free)
{
	if (*to_free == NULL)
		return ;
	free(*to_free);
	*to_free = NULL;
}
