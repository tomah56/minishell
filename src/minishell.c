/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:30:40 by ttokesi           #+#    #+#             */
/*   Updated: 2022/01/24 15:07:33 by ttokesi          ###   ########.fr       */
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

	create_environment(&data, envp);
	save_paths(&data, envp);

	tokdat.qudouble = 0;
	tokdat.qusingle = 0;
	data.cmds = malloc(sizeof(t_cmds)); // segfoult whitout malloc... not sure.
	data.cmds->tokens = &tokdat;
	temp = "not";
	while (temp)
	{
		temp = readline("HAKUNA MATATA 0.01$ ");
		add_history(temp);

		if (!ft_strncmp(temp, "exit", 5))
		{
			//exit has numbers in the end setting the exit status exxit also should return with rror massages
			// exit ode goes until 255 then restarts exit 256 will show $? 0 | 511 --> 255 | 512 --> 0...
			//  4294967295
			//  25600000000000000001 --> 255 too much
			//  2560000000000000001 -->1 still works
			//  9223372036854775808 long long -- > 255
			//  9223372036854775807 long long -- > 255
			//  9223372036854775806 long long -- > 254
			//  -1 --- > 255
			//  -2 --- > 254
			//  -255 --- > 1
			//  -256 --- > 0
			//  -9223372036854775808 long long -- > 0
			//  -9223372036854775809 long long -- > 255
			//  - ...rest-->255
			// too big or too small number it returns error  but still exits
			// bash-3.2$ exit -9223372036854775809
			// exit
			// bash: exit: -9223372036854775809: numeric argument required
			// we should handle '-f' lags as stings and send "numberic argument requered massage"
			//like this too
			// bash-3.2$ exit hello
			// exit
			// bash: exit: hello: numeric argument required
			
			// too many arguments doesnt exit
			// bash-3.2$ exit 5 5 
			// exit
			// bash: exit: too many arguments

			// too many not numeric still exits
			// bash-3.2$ exit b b
			// exit
			// bash: exit: b: numeric argument required

			// exits normaly
			// bash-3.2$ exit "55" also '55' both quote sign wroks
			// exit
			// ttokesi@3-F-11 Documents % 

			// bash-3.2$ exit "'8'"
			// exit
			// bash: exit: '8': numeric argument required
			// ttokesi@3-F-11 Documents % 

			// bash-3.2$ exit ""8''
			// exit
			// ttokesi@3-F-11 Documents % echo $?
			// 8
				// hope this all the edges...
			free(temp);

			temp = NULL;
		
		}
		else
		{
			input_one(temp, &tokdat, 0, 0);
			// printf("%s\n", temp);
		}
	}
	printf("I m here\n");

	// free cmds also...
	// free **tokensfull and every pointer inside in the end
	return (0);
}

// Function: int rl_on_new_line ()
// Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline. 
// Function: int rl_redisplay ()
// Change what's displayed on the screen to reflect the current contents of rl_line_buffer. 
//   rl_clear_history, ?????
//  rl_replace_line, ????? 