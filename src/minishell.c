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

static void	print_command_array(t_data *data)
{
	t_cmds	*temp_c;
	int		i;

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

static void	rec_sig(int num)
{
	rl_on_new_line();
	rl_redisplay();
	write(2, "  \b\b", 5);
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

void	make_routine(t_data *data, char *temp)
{
	data->i = 0;
	data->j = 0;
	data->k = 0;
	input_one_lilist(temp, data);
	printf("HERE\n");
	link_expand_looper(data);
	bypass_juntion(data);
	in_out_file_looper(data);
	remove_linklist_file_looper(data);
	commands_link_to_array_looper(data); // puts the linklist to the array
	// printlist(&data);
	// execute_the_ii(&data);
	// execute(data);
}

void	minishell(t_data	*data)
{
	t_tok	tokdat;
	char	*temp;
	char	**exp;
	char	*home;

	temp = "not";
	while (temp)
	{
		data->qudouble = 0;
		data->qusingle = 0;
		temp = readline("HAKUNA MATATA 0.42$ ");
		add_history(temp);
		if (!ft_strncmp(temp, "exit", 5))
		{
			free(temp);
			temp = NULL;
			free_struct(data);
			ft_free_array(data->environ);
			data->environ = NULL;
		}
		else
			make_routine(data, temp);
		free_struct(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	signal(SIGQUIT, rec_sig);
	signal(SIGINT, rec_sig);
	// signal(SIGINT, myhandler);
	// signal(SIGTERM, myhandler);
	create_environment(&data, envp);
	minishell(&data);
	ft_free_3array(&data.environ);
	data.environ = NULL;
	free_struct(&data);
	system("leaks minishelll");
	return (0);
}
