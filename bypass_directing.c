#include "../include/minishell.h"

int	file_opener(char *filtogo, t_data * data)
{
	char	*temp;
	int		size;
	int fd;

	if (filtogo == NULL)
	{
		write(2, "ERROR\n",6);
		return (-1); // bash: syntax error near unexpected token `newline'
	}
	fd = open(filtogo, O_WRONLY | O_CREAT | O_APPEND, 0644); //which mode do we need?
	if (fd == FAILED)
	{
		write(2, "ERROR\n",6); // temperarrly
		return (-1);
	}
	close(fd);
	return (fd);
}

t_tok *by_pa_norm(t_tok *temp_t, t_cmds	*temp_c, t_data *data)
{
	t_tok	*temp_t2;

	temp_t = (temp_t)->next;
	if (!ft_strncmp((temp_t)->content, "<", 1))
	{
		temp_t2 = (temp_t)->prev->prev; // becaouse of the deleting middle guys
		(temp_t)->infile = file_opener((temp_t)->content, data);
		remove_node(&data->cmds->tokens, (temp_t)->prev); // freeeing content is not working... is it a leak???
		remove_node(&data->cmds->tokens, (temp_t));
		temp_t = temp_t2;
	}
	if (!ft_strncmp((temp_t)->content, "<", 1))
	{
		temp_t2 = (temp_t)->prev->prev; // becaouse of the deleting middle guys
		(temp_t)->outfile = file_opener((temp_t)->content, data);
		remove_node(&data->cmds->tokens, (temp_t)->prev); // freeeing content is not working... is it a leak???
		remove_node(&data->cmds->tokens, (temp_t));
		temp_t = temp_t2;
	}
	return (temp_t);
}

void	bypass_juntion(t_data *data)
{
	t_tok	*temp_t;
	t_cmds	*temp_c;

	temp_t = data->cmds->tokens;
	temp_c = data->cmds;
	while (temp_c != NULL)
	{
		temp_t = temp_c->tokens;
		while (temp_t != NULL)
		{
			temp_t = by_pa_norm(temp_t, temp_c, data);
		}
		temp_c = temp_c->next;
	}
}