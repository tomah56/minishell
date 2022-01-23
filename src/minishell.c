/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:30:40 by ttokesi           #+#    #+#             */
/*   Updated: 2022/01/23 21:56:09 by ttokesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

// void myhandler(int num)
// {
// 	write(STDOUT_FILENO, " I will never die!\n", 18);
// }


int	main(int argc, char **argv, char **envp)
{
	t_tok tokdat;
	char *temp;
	t_data	data;
	

	// signal(SIGINT, myhandler);
	// signal(SIGTERM, myhandler);

	// write(1,"minishe master$ ", 16);
	// execve("/bin/echo", &argv[1], envp); // runs things in enviroment you are in 
	int i = 1;
	while (i < argc)
	{
		printf("%s\n", argv[i]);
		i++;
	}
	create_environment(&data, envp);
	save_paths(&data, envp);
	tokdat.data = &data;

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
	printf("I m here\n");
	return (0);
}

// Function: int rl_on_new_line ()
// Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline. 
// Function: int rl_redisplay ()
// Change what's displayed on the screen to reflect the current contents of rl_line_buffer. 
//   rl_clear_history, ?????
//  rl_replace_line, ????? 