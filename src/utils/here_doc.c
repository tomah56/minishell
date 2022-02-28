/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 20:54:40 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/21 17:02:17 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	h_doc_to_file(int fd, char *str)
{
	if (fd == -2)
		fd = open("temp.txt", O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
	{
		write(fd, &str, ft_strlen(str));
		write(fd, "\n", 1);
	}
}

static char	*here_doc_to_string(char *stop, t_data *data)
{
	char	*temp;
	char	*superholder;
	int		size;

	if (stop == NULL)
		return (NULL); // bash: syntax error near unexpected token `newline'
	superholder = NULL;
	size = ft_strlen(stop);
	temp = readline(">");
	while (ft_strncmp(temp, stop, size) || temp[size] != '\0')
	{
		if (superholder == NULL)
		{
			superholder = ft_strdup(temp);
		}
		else
			superholder = ft_strjoin(superholder, temp);
			//question should we save the new lines too???? curently it oes not do that
			//also maybe is not enough to save it in a string it needs a file descriptor?
		temp = readline(">");
	}
	return (superholder);
}

static bool	is_last_heredoc_in_cmd(t_tok **temp_t)
{
	int	i;

	i = 0;
	while ((*temp_t)->next != NULL)
	{
		if (!(ft_strncmp((*temp_t)->content, "<<", 3)))
		{
			while (i != 0)
			{
				*temp_t = (*temp_t)->prev;
				i--;
			}
			return (false);
		}
		*temp_t = (*temp_t)->next;
		i++;
	}
	while (i != 0)
	{
		*temp_t = (*temp_t)->prev;
		i--;
	}
	return (true);
}

void	here_doc(char *stop, t_data *data, t_cmds *temp_c, t_tok **temp_t)
{
	char	*temp;
	int		size;
	int		heredocfd[2];

	if (stop == NULL)
	{
		write(2, "ERROR\n", 6);
		return ; // bash: syntax error near unexpected token `newline'
	}
	if (pipe(heredocfd) == -1)
		msg_exit(data, "pipe error\n");
	size = ft_strlen(stop);
	temp = readline(">");
	if (temp == NULL)
		return ;
	while (ft_strncmp(temp, stop, size) || temp[size] != '\0')
	{
		temp = no_expand_next_part_no(temp, data);
		write(heredocfd[WRITE], temp, ft_strlen(temp));
		write(heredocfd[WRITE], "\n", 1);
		temp = readline(">");
		if (temp == NULL)
			return ;
	}
	close(heredocfd[WRITE]);
	if (is_last_heredoc_in_cmd(temp_t))
		close(heredocfd[READ]);
	else
		temp_c->heredoc = heredocfd[READ];
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
