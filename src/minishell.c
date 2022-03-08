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

void printlist(t_data *data)
{
	t_data *temp;
	t_tok *temp_t;
	t_cmds *temp_c;
	int i = 1;
	int j = 1;

	temp = data;
	i = 0;
	
	temp_c = data->cmds;

	temp_t = temp_c->tokens;
	while (temp_c != NULL)
	{
		temp_t = temp_c->tokens;
		printf("CMDS %d  number of tokens: %d\n", j, count_tokens(temp_c));
		printf("infile %d  outfile: %d\n", temp_c->infile, temp_c->outfile);
		printf("LAST %d", temp_c->last);
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
}

void	make_routine(t_data *data, char *temp)
{
	data->i = 0;
	data->j = 0;
	data->k = 0;
	data->falg = 1;
	// printf("---1 %p \n",temp);
	if (input_one_lilist(temp, data))
		return ;
	if (link_expand_looper(data))
		return ;
	// printlist(data);
	// printf("hello 1\n");
	if (bypass_juntion(data, 0))
		return ;
	printf("hello 0\n");
	in_out_file_looper(data);
	remove_linklist_file_looper(data);
	sytax_looper(data);
	commands_link_to_array_looper(data);
	// printlist(data);
	// printf("in: %d, out %d\n", data->cmds->infile, data->cmds->outfile);
	check_for_builtins(data);
	// printf("hello 2\n");
	if (data->falg == 1)
		execute(data);
	if (data->cmds != NULL)
		free(data->cmds->commands);
	// printf("hello 3\n");
	// printf("in: %d, out %d\n", data->cmds->infile, data->cmds->outfile);
}

void	minishell(t_data *data)
{
	char	*temp;

	temp = NULL;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, rec_sig);
		data->qudouble = 0;
		data->qusingle = 0;
		data->tokentotal = 0;
		data->save_fd = ft_dup(data, STDIN_FILENO);
		if (temp != NULL)
			free(temp);
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
		// system("leaks minishellll");
		// fscanf(stdin, "c");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	create_environment(&data, envp);
	minishell(&data);
	close(data.save_fd);
	ft_free_3array(&data.environ);
	data.environ = NULL;
	free_struct(&data);
	printf("HERE\n");
	(void)argc;
	(void)argv;
	return (0);
}
