/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:30:40 by ttokesi           #+#    #+#             */
/*   Updated: 2022/01/26 17:13:44 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */





#include "../include/minishell.h"

// void myhandler(int num)
// {
// 	write(STDOUT_FILENO, " I will never die!\n", 18);
// }

void	printlist(t_data *data)
{
	t_data	*temp;
	t_tok	*temp_t;
	t_cmds *temp_c;
	int i = 1;
	int j = 1;

	temp = data;
	// while (temp != NULL)
	// {
	// 	printf("CMD LIST NR: %d\n", i);
	// 	printf("-INFILE: %d - \n", temp->cmds->infile);
	// 	printf("-OUTFILE: %d - \n", temp->cmds->outfile);
	// 	printf("COMMANDS: %s - \n", temp->cmds->commands); //commands doube pointer
	// 	temp = temp->cmds->next;
	// 	i++;
	// }
		// printf("CONTENT: %s - \n", temp_t->content);
	i = 0;
	temp_t = data->cmds->tokens;
	temp_c = data->cmds;
	while (temp_c != NULL)
	{
		printf("CMDS %d\n", j);
		temp_t = temp_c->tokens;
		while (temp_t != NULL)
		{
			// printf("TOKEN LIST NR: %d\n", i);
			// printf("TYPE: %d - \n", temp_t->cmds->tokens->type);
			// printf("QUOTE_TYPE: %d - \n", temp->cmds->tokens->quote_type);
			printf("%s-->", temp_t->content);
			temp_t = temp_t->next;
			i++;
		}
		temp_c = temp_c->next;
		j++;
		printf("\n");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_tok tokdat;
	char *temp;
	t_data	data;
	char **exp;
	// t_cmds	*cmds;
	

	// signal(SIGINT, myhandler);
	// signal(SIGTERM, myhandler);

	// write(1,"minishe master$ ", 16);
	// execve("/bin/echo", &argv[1], envp); // runs things in enviroment you are in 

	create_environment(&data, envp);
	save_paths(&data, envp);
	data.qudouble = 0;
	data.qusingle = 0;
	data.i = 0;
	data.j = 0;
	// cmds = NULL;
	// data.cmds = create_new_cmds_node(&data);
	// data.cmds->tokens = create_new_token_node(&data);
	// printlist(&data);
	// data.cmds = malloc(sizeof(t_cmds)); // segfoult whitout malloc... not sure.
	// data.cmds->tokens = &tokdat;
	temp = "not";
	while (temp)
	{
		temp = readline("HAKUNA MATATA 0.01$ ");
		add_history(temp);
		// rl_on_new_line();
		// rl_replace_line("klklk\n", 8);
		// rl_redisplay(); //cotr -c cotr D
		// rl_clear_history();


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
		else if (!ft_strncmp(temp, "pwd", 4) || !ft_strncmp(temp, "pwd ", 5))
		{
			builtin_pwd(&data);
		}
		else if (!ft_strncmp(temp, "env", 4))
		{
			builtin_env(&data);
		}
		else
		{
			// input_one_array(temp, &tokdat, 0, 0);
			input_one_lilist(temp, &data, 0, 0);
			// printf("content %s\n", data.cmds->tokens->next->content);
			printlist(&data);
			// printf("command: %d",count_list_elements(&data, 1));
		}
	}
	// printf("I m here\n");
	// rl_rep

	// free cmds also...
	// free **tokensfull and every pointer inside in the end
	return (0);
}


// bash-3.2$ pwdfhuhfuhufhfuhufhf fkjfkjf
// bash: pwdfhuhfuhufhfuhufhf: command not found
// bash-3.2$ pwd 999999999999
// /Users/ttokesi/Documents

// Function: int rl_on_new_line ()
// Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline. 
// Function: int rl_redisplay ()
// Change what's displayed on the screen to reflect the current contents of rl_line_buffer. 
//   rl_clear_history, ?????
//  rl_replace_line, ????? 
