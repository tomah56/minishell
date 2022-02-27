/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 23:27:07 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/27 23:28:23 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_only(t_data *data)
{
	char	**exp;
	int		i;

	if (data->environ[0] == NULL)
		return ;
	else
	{
		exp = ft_calloc(ft_strlen_double(data->environ) + 1, sizeof(char *));
		if (exp == NULL)
			msg_exit(data, "malloc error");
		i = 0;
		while (data->environ[i])
		{
			exp[i] = ft_strdup(data->environ[i]);
			i++;
		}
		exp = sort_env(exp);
	}
	print_export(data, exp);
	ft_free_array(exp);
	g_exit = 0;
}

void	print_export(t_data *data, char **exp)
{
	int		i;
	int		j;
	int		len;
	char	*var_name;
	char	*var;

	i = 0;
	while (exp[i] != NULL)
	{
		len = ft_strlen(exp[i]);
		j = 0;
		while (exp[i][j] && exp[i][j] != '=')
			j++;
		j = j + 1;
		var_name = ft_substr(exp[i], 0, j);
		var = ft_substr(exp[i], j, (len - j));
		printf("%s", var_name);
		printf("\"%s\"\n", var);
		free(var_name);
		free(var);
		i++;
	}
}
