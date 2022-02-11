#include "../include/minishell.h"

static void	in_out_norm(t_tok **temp_t, t_cmds	*temp_c, t_data *data)
{
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
			temp_c->infile = temp_t->infile;
			temp_c->outfile = temp_t->outfile;
			// if (temp_t->prev != NULL)
			// {
			// 	close(temp_t->prev->infile);
			// 	close(temp_t->prev->outfile);
			// }
			// in_out_norm(&temp_t, temp_c, data);
			temp_t = (temp_t)->next;
		}
		temp_c = temp_c->next;
	}
}

// shaise 