#include "../include/minishell.h"

static t_tok	*only_heredoc(t_data *data, t_cmds	*temp_c)
{
	t_tok	*temp_t;

	temp_t = NULL;
	if (count_commands(data) == 1)
		exit(EXIT_SUCCESS);
	remove_node_c(&data->cmds, temp_c);
	return (temp_t);
}

static void	in_out_norm(t_tok **temp_t, t_cmds	*temp_c, t_data *data)
{
	t_tok	*temp_t2;

	if ((*temp_t)->bedeleted == 1)
	{
		temp_t2 = (*temp_t)->next->next;
		*temp_t = (*temp_t)->next;
		if (count_tokens(temp_c) == 2)
			*temp_t = only_heredoc(data, temp_c);
		else
		{
			remove_node(&temp_c->tokens, (*temp_t)->prev); // freeeing content is not working... is it a leak???
			remove_node(&temp_c->tokens, (*temp_t));
			*temp_t = temp_t2;
		}
	}
	// *temp_t = (*temp_t)->next;
	return ;
}


void	in_out_file_looper(t_data *data)
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
			if (temp_c->infile != -1)
				temp_c->infile = temp_t->infile;
			if (temp_c->outfile != -1)
				temp_c->outfile = temp_t->outfile;
			in_out_norm(&temp_t, temp_c, data);


			// if (temp_t->prev != NULL)
			// {
			// 	close(temp_t->prev->infile);
			// 	close(temp_t->prev->outfile);
			// }
			temp_t = (temp_t)->next;
		}
		temp_c = temp_c->next;
	}
}

// shaise 