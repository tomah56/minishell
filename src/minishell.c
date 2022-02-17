<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:30:40 by ttokesi           #+#    #+#             */
/*   Updated: 2022/02/16 17:33:16 by sreinhol         ###   ########.fr       */
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
	t_cmds	*temp_c;
	int i = 1;
	int j = 1;

	temp = data;
	i = 0;
	// issue looping over can be fixed with deleting mother linked list elements if the toen is NULL 
	temp_c = data->cmds;
	// while (temp_c->tokens == NULL) // this one segfaulted when list elements were deleted
	// {
	// 	if (temp_c != NULL)
	// 		temp_c = temp_c->next;
	// }
	// if (temp_c->tokens == NULL) // this one segfaulted when list elements were deleted
	// 	return ;
	temp_t = temp_c->tokens;
	while (temp_c != NULL)
	{
		temp_t = temp_c->tokens;
		printf("CMDS %d  number of tokens: %d INFILE: %d OUTFILE: %d\n", j, count_tokens(temp_c), temp_c->infile, temp_c->outfile);
		printf("infile %d  outfile: %d\n", temp_c->infile, temp_c->outfile);
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

static void print_command_array(t_data *data)
{
	t_cmds	*temp_c;
	int	i;

	temp_c = data->cmds;
	while (temp_c != NULL)
	{
		i = 0;
		while (temp_c->commands[i] != NULL)
		{
			printf("%s\n", temp_c->commands[i]);
			i++;
		}
		temp_c = temp_c->next;
	}
}

int	g_exit = 0;

static void	rec_sig(int num)
{	
	rl_on_new_line();
	rl_redisplay();
	write(2, "  \b\b", 5);
	// printf("%d\n", num);
	if (num == 2)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	// if (num == 3)
	// 	exit(EXIT_FAILURE);
	if (num == 15)
		exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_tok tokdat;
	char *temp;
	t_data	data;
	char **exp;
	char *home;
	// t_cmds	*cmds;
	// signal(SIGTERM, rec_sig);
	signal(SIGQUIT, rec_sig);
	signal(SIGINT, rec_sig);
	// signal(SIGINT, myhandler);
	// signal(SIGTERM, myhandler);
	create_environment(&data, envp);
	temp = "not";
	while (temp)
	{
		data.qudouble = 0;
		data.qusingle = 0;
		temp = readline("HAKUNA MATATA 0.42$ ");
		// if (temp == NULL) //printf also send EOF signal... problem
		// {
		// 	write(2, "\x1b[1A", 4);
		// 	write(2, "\x1b[19C", 5);
		// 	write(2, " exit\n", 6);
		// 	exit(EXIT_SUCCESS);
		// }
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
		else
		{
			// input_one_array(temp, &tokdat, 0, 0);
			data.i = 0;
			data.j = 0;
			data.k = 0;
			input_one_lilist(temp, &data);
			link_expand_looper(&data);
			bypass_juntion(&data);
			in_out_file_looper(&data);
			remove_linklist_file_looper(&data);
			commands_link_to_array_looper(&data); // puts the linklist to the array
			// printlist(&data);
			// execute_the_ii(&data);
			execute(&data);
			// if (count_commands(&data) == 1)
				// execute_one_cmd(&data);
				// execute(&data);
			// print_command_array(&data);
			// print_command_array(&data);
			// execve("usr/bin/echo", data.cmds->commands, data.environ);
		}
	}
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
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:30:40 by ttokesi           #+#    #+#             */
/*   Updated: 2022/02/12 23:55:50 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void myhandler(int num)
// {
// 	write(STDOUT_FILENO, " I will never die!\n", 18);
// }

void printlist(t_data *data)
{
	t_data *temp;
	t_tok *temp_t;
	t_cmds *temp_c;
	int i = 1;
	int j = 1;

	temp = data;
	i = 0;
	// issue looping over can be fixed with deleting mother linked list elements if the toen is NULL
	temp_c = data->cmds;
	// while (temp_c->tokens == NULL) // this one segfaulted when list elements were deleted
	// {
	// 	if (temp_c != NULL)
	// 		temp_c = temp_c->next;
	// }
	// if (temp_c->tokens == NULL) // this one segfaulted when list elements were deleted
	// 	return ;
	temp_t = temp_c->tokens;
	while (temp_c != NULL)
	{
		temp_t = temp_c->tokens;
		printf("CMDS %d  number of tokens: %d\n", j, count_tokens(temp_c));
		printf("infile %d  outfile: %d\n", temp_c->infile, temp_c->outfile);
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

static void print_command_array(t_data *data)
{
	t_cmds *temp_c;
	int i;

	temp_c = data->cmds;
	while (temp_c != NULL)
	{
		i = 0;
		while (temp_c->commands[i] != NULL)
		{
			printf("%s\n", temp_c->commands[i]);
			i++;
		}
		temp_c = temp_c->next;
	}
}

int g_exit = 0;

static void rec_sig(int num)
{
	rl_on_new_line();
	rl_redisplay();
	write(2, "  \b\b", 5);
	// printf("%d\n", num);
	if (num == 2)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	// if (num == 3)
	// 	exit(EXIT_FAILURE);
	if (num == 15)
		exit(EXIT_FAILURE);
}

int main(int argc, char **argv, char **envp)
{
	t_tok tokdat;
	char *temp;
	t_data data;
	char **exp;
	char *home;
	// t_cmds	*cmds;
	// signal(SIGTERM, rec_sig);
	signal(SIGQUIT, rec_sig);
	signal(SIGINT, rec_sig);

	// signal(SIGINT, myhandler);
	// signal(SIGTERM, myhandler);
	create_environment(&data, envp);

	temp = "not";
	while (temp)
	{
		data.qudouble = 0;
		data.qusingle = 0;
		temp = readline("HAKUNA MATATA 0.42$ ");
		// if (temp == NULL) //printf also send EOF signal... problem
		// {
		// 	write(2, "\x1b[1A", 4);
		// 	write(2, "\x1b[19C", 5);
		// 	write(2, " exit\n", 6);
		// 	exit(EXIT_SUCCESS);
		// }
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
		else
		{
			// input_one_array(temp, &tokdat, 0, 0);
			data.i = 0;
			data.j = 0;
			data.k = 0;
			input_one_lilist(temp, &data);
			// printf("content %s\n", data.cmds->tokens->next->content);
			link_expand_looper(&data);
			bypass_juntion(&data);
			in_out_file_looper(&data);
			remove_linklist_file_looper(&data);
			commands_link_to_array_looper(&data); // puts the linklist to the array
			execute_the_ii(&data);
			// if (count_commands(&data) == 1)
			// execute_one_cmd(&data);
			// execute(&data);
			// print_command_array(&data);
			printlist(&data);
			
			// print_command_array(&data);
			// execve("usr/bin/echo", data.cmds->commands, data.environ);
		}
	}

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
>>>>>>> 8404107a3028bac01db4c43abc965d55b0bfe479
