#include "../include/minishell.h"

int	file_opener(char *filtogo, t_data * data)
{
	char	*temp;
	int		size;
	int fd;

	// close(fd); // when we loop over to find the latest one we close the previous ones
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
	return (fd);
}

void not_working_by_pa_norm(t_tok **temp_t, t_cmds	*temp_c, t_data *data)
{
	t_tok	*temp_t2;

	if (!ft_strncmp((*temp_t)->content, ">", 1))
	{
		ot_remove_node(&temp_c->tokens, (*temp_t));
		*temp_t = (*temp_t)->next;
		(*temp_t)->outfile = file_opener((*temp_t)->content, data);
		ot_remove_node(&temp_c->tokens, (*temp_t));


		
	}
	else if (!ft_strncmp((*temp_t)->content, "<", 1))
	{
		ot_remove_node(&temp_c->tokens, (*temp_t));
		*temp_t = (*temp_t)->next;
		(*temp_t)->infile = file_opener((*temp_t)->content, data);
		ot_remove_node(&temp_c->tokens, (*temp_t));
	}
	if (*temp_t && (*temp_t)->next)
		*temp_t = (*temp_t)->next;
	else
		*temp_t = NULL;
}

void by_pa_norm(t_tok **temp_t, t_cmds	*temp_c, t_data *data)
{
	t_tok	*temp_t2;

	if (!ft_strncmp((*temp_t)->content, ">", 1))
	{
		temp_t2 = (*temp_t)->next->next;
		*temp_t = (*temp_t)->next;
		(*temp_t)->outfile = file_opener((*temp_t)->content, data);
		if (count_tokens(temp_c) == 2)
			*temp_t = only_heredoc(data, temp_c);
		else
		{
			remove_node(&temp_c->tokens, (*temp_t)->prev); // freeeing content is not working... is it a leak???
			remove_node(&temp_c->tokens, (*temp_t));
			*temp_t = temp_t2;
		}
	}
	else if (!ft_strncmp((*temp_t)->content, "<", 1))
	{
		temp_t2 = (*temp_t)->next->next;
		*temp_t = (*temp_t)->next;
		(*temp_t)->infile = file_opener((*temp_t)->content, data);
		if (count_tokens(temp_c) == 2)
			*temp_t = only_heredoc(data, temp_c);
		else
		{
			remove_node(&temp_c->tokens, (*temp_t)->prev); // freeeing content is not working... is it a leak???
			remove_node(&temp_c->tokens, (*temp_t));
			*temp_t = temp_t2;
		}
	}
	else
		*temp_t = (*temp_t)->next;
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
			by_pa_norm(&temp_t, temp_c, data);
		}
		temp_c = temp_c->next;
	}
}
