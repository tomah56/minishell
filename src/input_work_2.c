/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_work_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:12:01 by ttokesi           #+#    #+#             */
/*   Updated: 2022/01/23 16:15:38 by ttokesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int input_two(t_tok *tokdat)
{
	int i;

	i = 0;
	while (tokdat->tokensfull[i])
	{
		printf("%s\n", tokdat->tokensfull[i]);
		i++;
	}
	return (1);
}