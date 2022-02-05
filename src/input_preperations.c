
#include "../include/minishell.h"

char *l_e_loop_sequence(char *srt, t_data *data)
{
	char *temp;

	temp = expand_next_part(srt, data);
	free(srt);
	temp = quote_cutter(temp, 0, 0);
	return (temp);
}


void	link_expand_looper(t_data *data)
{
	t_tok	*temp_t;
	t_cmds	*temp_c;
	char	*temp;
	int		i;

	temp_t = data->cmds->tokens;
	temp_c = data->cmds;
	while (temp_c != NULL)
	{
		temp_t = temp_c->tokens;
		i = 0;
		while (temp_t != NULL)
		{
			if (ft_strncmp(temp_t->content, "<<", 2))
				temp_t->content = l_e_loop_sequence(temp_t->content, data); //leak danger
			else
			{
				unlink("./temp.txt"); // if multiple heredoc in one command it always start with clean file
				// remove_node(&data->cmds->tokens, temp_t->prev);  // this shit is not working
				temp_t = temp_t->next;
				temp_c->infile = here_doc(quote_cutter(temp_t->content, 0, 0), data);


			}
			temp_t = temp_t->next;
			i++;
		}
		// temp_c->commands = temp;
		temp_c = temp_c->next;
		free(temp);
	}
}

// something looping over this
// char *temp2;
// temp2 = expand_next_part(data.cmds->commands[0], &data);

void data_load(char *temp, t_data *data)
{
	input_one_lilist(temp, data);


}