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
		printf("type %d  \n", temp_c->type);
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
	data->falg = 1;
	input_one_lilist(temp, data);
	link_expand_looper(data);
	// printlist(data);
	bypass_juntion(data);
	in_out_file_looper(data);
	remove_linklist_file_looper(data);
	commands_link_to_array_looper(data);
	// printlist(data);
	check_for_builtins(data);
	if (data->falg == 1)
		execute(data);
}

void	minishell(t_data *data)
{
	t_tok	tokdat;
	char	*temp;
	char	**exp;
	char	*home;

	temp = NULL;
	data->save_fd = ft_dup(data, STDIN_FILENO);
	while (1)
	{
		data->qudouble = 0;
		data->qusingle = 0;
		temp = readline("HAKUNA MATATA 0.42$ ");
		if (temp == NULL)
		{
			write(2, "\x1b[1A", 4);
			write(2, "\x1b[19C", 5);
			write(2, " exit\n", 6);
			exit(EXIT_SUCCESS);
		}
		add_history(temp);
		if (temp[0] == '\0')
		{
			free_struct(data);
			continue ;
		}
		make_routine(data, temp);
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
	close(data.save_fd);
	ft_free_3array(&data.environ);
	data.environ = NULL;
	free_struct(&data);
	return (0);
}
