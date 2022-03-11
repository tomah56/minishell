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

int	g_exit = 0;

static void	rec_sig(int num)
{
	rl_on_new_line();
	rl_redisplay();
	write(2, "  \b\b", 5);
	if (num == 2)
	{
		write(2, "\n", 1);
		g_exit = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static int	make_routine(t_data *data, char *temp)
{
	data->i = 0;
	data->j = 0;
	data->k = 0;
	data->qudouble = 0;
	data->qusingle = 0;
	data->tokentotal = 0;
	data->falg = 1;
	if (input_one_lilist(temp, data) || *temp == '\0')
		return (free_struct_sig(data));
	if (link_expand_looper(data))
		return (free_struct_sig(data));
	if (bypass_juntion(data, 0))
		return (free_struct_sig(data));
	in_out_file_looper(data);
	remove_linklist_file_looper(data);
	sytax_looper(data);
	commands_link_to_array_looper(data);
	check_for_builtins(data);
	if (data->falg == 1)
		execute(data);
	if (data->cmds != NULL)
		free(data->cmds->commands);
	return (0);
}

static int	why_again(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

static void	minishell(t_data *data)
{
	char	*temp;

	temp = NULL;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, rec_sig);
		if (temp != NULL && why_again(temp))
			free(temp);
		temp = readline("HAKUNA MATATA 4.2$ ");
		if (temp == NULL)
			write(2, "\x1b[1A\x1b[19C exit\n", 15);
		if (temp == NULL)
			exit(130);
		if (temp[0] != '\0')
			add_history(temp);
		if (temp[0] == '\0')
			continue ;
		data->save_fd = ft_dup(data, STDIN_FILENO);
		if (why_again(temp))
			make_routine(data, temp);
		close(data->save_fd);
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
	(void)argc;
	(void)argv;
	return (0);
}
