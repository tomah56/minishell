/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:30:40 by ttokesi           #+#    #+#             */
/*   Updated: 2022/01/23 18:01:29 by ttokesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tok tokdat;
	char *temp;
	t_data	data;

	// write(1,"minishe master$ ", 16);
	execve("/bin/echo", &argv[1], envp); // runs things in enviroment you are in 
	create_environment(&data, envp);
	tokdat.qudouble = 0;
	tokdat.qusingle = 0;
	// temp = "not";
	// while (temp)
	// {
	// 	temp = readline("minishe master$ ");
	// 	add_history(temp);
	// 	// int i = 0;
	// 	// while (temp[i] != '\0')
	// 	// {
	// 	// 	i++;
	// 	// }
	// 	// printf("we have the end of the string %d\n", i);
	// 	if (!ft_strncmp(temp, "exit", 5))
	// 	{
	// 		free(temp);
	// 		temp = NULL;
		
	// 	}
	// 	else
	// 	{
	// 		input_one(temp, &tokdat, 0, 0);
	// 		// printf("%s\n", temp);
	// 	}
	// }

	return (0);
}

// Function: int rl_on_new_line ()
// Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline. 
// Function: int rl_redisplay ()
// Change what's displayed on the screen to reflect the current contents of rl_line_buffer. 
//   rl_clear_history, ?????
//  rl_replace_line, ????? 