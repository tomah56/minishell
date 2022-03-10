/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_preperations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 22:05:00 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/17 22:05:00 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*hd_name_maker(long number)
{
	char	*base;
	char	*temp;
	long	num1;
	int		i;

	temp = malloc(17);
	base = "0123456789abcdef";
	num1 = number;
	temp[0] = '.';
	temp[1] = '/';
	temp[2] = 't';
	temp[3] = '/';
	i = 4;
	while (num1 >= 16)
	{
		temp[i] = base[num1 % 16];
		num1 = num1 / 16;
		i++;
	}
	temp[i] = base[num1 % 16];
	temp[i + 1] = '.';
	temp[i + 2] = 'd';
	temp[i + 3] = 'e';
	temp[i + 4] = '\0';
	return (temp);
}

char	*l_e_loop_sequence(char *str, t_data *data)
{
	char	*temp;
	char	*temp1;

	temp = expand_next_part(str, data);
	temp1 = temp;
	free(str);
	free(temp);
	temp = quote_cutter(temp1, 0, 0);
	return (temp);
}

static int	l_e_l_norm(t_tok **temp_t, t_cmds *temp_c, t_data *data)
{
	char	*name;
	char	*stop;

	if (ft_strncmp((*temp_t)->content, "<<", 3))
	{
		(*temp_t)->content = l_e_loop_sequence((*temp_t)->content, data);
		*temp_t = (*temp_t)->next;
	}
	else
	{
		name = hd_name_maker((unsigned long)temp_c);
		unlink(name);
		(*temp_t)->bedeleted = 1;
		*temp_t = (*temp_t)->next;
		if (syntax_rutine(temp_t) == -1)
			return (-1);
		(*temp_t)->bedeleted = 1;
		(*temp_t)->outfile = -1;
		(*temp_t)->hd_file = name;
		stop = quote_cutter((*temp_t)->content, 0, 0);
		(*temp_t)->infile = here_doc(stop, data, name);
		*temp_t = (*temp_t)->next;
		free(stop);
	}
	return (0);
}

int	link_expand_looper(t_data *data)
{
	t_tok	*temp_t;
	t_cmds	*temp_c;
	int		save_in;

	save_in = dup(STDIN_FILENO);
	temp_t = data->cmds->tokens;
	temp_c = data->cmds;
	while (temp_c != NULL)
	{
		temp_t = temp_c->tokens;
		temp_c->cm_hd_file = NULL;
		while (temp_t != NULL)
		{
			(temp_t)->bedeleted = 0;
			(temp_t)->infile = -1;
			(temp_t)->outfile = -1;
			(temp_t)->hd_file = NULL;
			if (l_e_l_norm(&temp_t, temp_c, data) == -1)
				return (1);
			dup2(save_in, STDIN_FILENO);
		}
		temp_c = temp_c->next;
	}
	close(save_in);
	return (0);
}

void	check_token_flags_li(char str, t_data *data)
{
	if (str == '"' && data->qudouble == 0 && data->qusingle == 0)
		data->qudouble = 1;
	else if (str == '"' && data->qudouble == 1 && data->qusingle == 0)
		data->qudouble = 0;
	if (str == '\'' && data->qusingle == 0 && data->qudouble == 0)
		data->qusingle = 1;
	else if (str == '\'' && data->qusingle == 1 && data->qudouble == 0)
		data->qusingle = 0;
}
