/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:30:40 by ttokesi           #+#    #+#             */
/*   Updated: 2022/02/08 21:21:26 by sreinhol         ###   ########.fr       */
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
	i = 0;
	temp_t = data->cmds->tokens;
	temp_c = data->cmds;
	while (temp_c != NULL)
	{
		temp_t = temp_c->tokens;
		printf("CMDS %d  number of tokens: %d\n", j, temp_c->comandcount);
		while (temp_t != NULL)
		{
			printf("%s[---]", temp_t->content);
			temp_t = temp_t->next;
			i++;
		}
		temp_c = temp_c->next;
		j++;
		printf("\n");
	}
}

int	g_exit = 0;

static void	rec_sig(int num)
{
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void new_prompt()
{
	char *temp;

	temp = "not";
	temp = readline("?");
	add_history(temp);
		// rl_on_new_line();
		// rl_replace_line("klklk\n", 8);
		// rl_redisplay(); //cotr -c cotr D
		// rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_tok tokdat;
	char *temp;
	t_data	data;
	char **exp;
	char *home;
	// t_cmds	*cmds;
	signal(SIGINT, rec_sig);
	

	// signal(SIGINT, myhandler);
	// signal(SIGTERM, myhandler);

	// write(1,"minishe master$ ", 16);
	// execve("/bin/echo", &argv[1], envp); // runs things in enviroment you are in 

	create_environment(&data, envp);
	save_paths(&data, envp);
	// builtin_echo(&data);
	// export_only(&data);
	// system("leaks minishelll");
	// cmds = NULL;
	// data.cmds = create_new_cmds_node(&data);
	// data.cmds->tokens = create_new_token_node(&data);
	// printlist(&data);
	// data.cmds = malloc(sizeof(t_cmds)); // segfoult whitout malloc... not sure.
	// data.cmds->tokens = &tokdat;
	temp = "not";
	while (temp)
	{
		data.qudouble = 0;
		data.qusingle = 0;
		temp = readline("HAKUNA MATATA 0.42$ ");
		add_history(temp);
		// rl_on_new_line();
		// rl_replace_line("klklk\n", 8);
		// rl_redisplay(); //cotr -c cotr D
		// rl_clear_history();


		if (!ft_strncmp(temp, "exit", 5))
		{
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
		else if (!ft_strncmp(temp, ">>", 4))
		{
			new_prompt();
		}
		else
		{
			// input_one_array(temp, &tokdat, 0, 0);
			data.i = 0;
			data.j = 0;
			data.k = 0;
			input_one_lilist(temp, &data);
			// printf("content %s\n", data.cmds->tokens->next->content);
			// printlist(&data);
			link_expand_looper(&data);
			//redirections
			// printf("\nexpand,qutecut:\n");
			printlist(&data);
			// printf("tokentotal: %d\n", data.tokentotal);
			// commands_link_to_array_looper(&data); // puts the linklist to the array

			// data.actual = data.cmds;
			// builtin_echo(&data);

			// char *temp2;
	
			// temp2 = expand_next_part(data.cmds->commands[0], &data);
			// printf("expander:->%s<-\n", temp2);
			// temp2 = quote_cutter(temp2, 0, 0);
			// printf("quoteremooval: ->%s<-\n", temp2);

		
			// free(temp2);
			// temp2 = NULL;

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


// bash-3.2$ cat | echo bubu
// bubu
// not error machage just waits... (WTF)
// bash-3.2$ cat | grep b
// b
// b
// b
// b
// c
// f

// d
// exit
// g
// ^C


