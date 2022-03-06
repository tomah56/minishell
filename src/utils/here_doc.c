/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 20:54:40 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/12 14:38:24 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	rec_sig_doc(int num)
{

	// write(2, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	write(2, "  \b\b", 5);
	if (num == 2)
	{
		write(2, " ", 1);
		rl_on_new_line();
		close(STDIN_FILENO);
	}
}

int	old_here_doc(char *stop, t_data *data, char *name)
{
	char	*temp;
	int		size;
	int		fd;
	// int		save_in;

	signal(SIGINT, rec_sig_doc);

	// save_in = dup(STDIN_FILENO);
	if (stop == NULL)
	{
		write(2, "ERROR\n", 6);
		return (-1); // bash: syntax error near unexpected token `newline'
	}
	fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0777);
	// fd = open("./temp/test.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd == FAILED)
	{
		write(2, "ERROR\n", 6); // temperarrly
		return (-1);
	}
	size = ft_strlen(stop);
	temp = readline(">"); // how is this gets inside my linked list????????
	if (temp == NULL)
	{
		close(fd);
		return (-1);
	}
	while (ft_strncmp(temp, stop, size) || temp[size] != '\0')
	{
		// dup2(save_in, STDIN_FILENO);
		temp = no_expand_next_part_no(temp, data);
		write(fd, temp, ft_strlen(temp));
		write(fd, "\n", 1);
		temp = readline(">");
		if (temp == NULL)
		{
			close(fd);
			return (-1);
		}
	}
	close(fd); //closing somwhere in the end....
	fd = open(name, O_RDONLY, 0777); // so apperantly its matter hof you open a file, good to know
	return (fd);
}

// heredoc scpeials
// bash-3.2$ << he grep b
// > b
// > b
// > he
// b
// b
// bash-3.2$ echo bobo << he grep b
// > b
// > s
// > he
// bobo grep b
// bash-3.2$ 
