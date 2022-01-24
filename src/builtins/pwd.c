/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:23:32 by sreinhol          #+#    #+#             */
/*   Updated: 2022/01/24 22:39:21 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_pwd(t_data *data)
{
	char	**temp_env;
	char	*path_pwd;
	char	**pwd;
	int		i;

	temp_env = data->environ;
	pwd = NULL;
	while (*temp_env != NULL && ft_strncmp(*temp_env, "PWD=", 4))
		*temp_env++;
	path_pwd = (*temp_env + 4);
	pwd = ft_split(path_pwd, ':');
	if (!pwd)
		msg_exit(data, "malloc error");
	i = 0;
	while (pwd[i] != NULL)
	{
		printf("%s", pwd[i]);
		i++;
	}
}




// void	execute_pwd(t_data *data)
// {
// 	char	*buff;

// 	buff = getcwd(NULL, 0);
// 	if (buff == NULL)
// 		msg_exit_malloc_error(data);
// 	printf("%s\n", buff);
// 	ft_free_1d((void **) &buff);
// 	g_errno = 0;
// }

// int	pwd(void)
// {
// 	char	*cwd;

// 	cwd = NULL;
// 	cwd = getcwd(cwd, 0);
// 	if (cwd == NULL)
// 	{
// 		perror("Error");
// 		return (EXIT_FAILURE);
// 	}
// 	else if (ft_printf("%s\n", cwd) != ft_strlen(cwd) + 1)
// 	{
// 		ft_free_str(&cwd);
// 		perror("\nError: printf failed");
// 		return (EXIT_FAILURE);
// 	}
// 	ft_free_str(&cwd);
// 	return (EXIT_SUCCESS);
// }
