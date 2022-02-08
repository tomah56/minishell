
#include "../include/minishell.h"

char *l_e_loop_sequence(char *srt, t_data *data)
{
	char *temp;

	temp = expand_next_part(srt, data);
	free(srt);
	temp = quote_cutter(temp, 0, 0);
	return (temp);
}

t_tok *l_e_l_norm(t_tok *temp_t, t_cmds	*temp_c, t_data *data)
{
	t_tok	*temp_t2;

	if (ft_strncmp((temp_t)->content, "<<", 2))
	{
		(temp_t)->content = l_e_loop_sequence((temp_t)->content, data); //leak danger
		temp_t = (temp_t)->next;
	}
	else
	{
		unlink("./temp.txt"); // if multiple heredoc in one command it always start with clean file... need separate name for separate commands problem
		temp_t = (temp_t)->next;
		temp_t2 = (temp_t)->prev->prev; // becaouse of the deleting middle guys
		(temp_t)->infile = here_doc(quote_cutter((temp_t)->content, 0, 0), data);
		printf("TOKENS: %d\n", count_tokens(temp_c));
		if (count_tokens(temp_c) == 2)
		{
			if (count_commands(data) == 1)
				exit(EXIT_SUCCESS);
			remove_node_c(&data->cmds, temp_c);
		}
		else
		{
			remove_node(&data->cmds->tokens, (temp_t)->prev); // freeeing content is not working... is it a leak???
			remove_node(&data->cmds->tokens, (temp_t));
			temp_t = temp_t2;
		}
	}
	return (temp_t);
}

// still segfoults
// << so << bo |<< ju
// >so
// zsh: segmentation fault  ./minishelll


void	link_expand_looper(t_data *data)
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
			temp_t = l_e_l_norm(temp_t, temp_c, data);
		}
		temp_c = temp_c->next;
	}
}

// something looping over this
// char *temp2;
// temp2 = expand_next_part(data.cmds->commands[0], &data);

void data_load(char *temp, t_data *data)
{
	input_one_lilist(temp, data);


}