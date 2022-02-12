#include "../include/minishell.h"

static	char	*hd_name_maker(long number)
{
	char	*base;
	char	*temp;
	long	num1;
	int		i;

	i = 0;
	temp = malloc(10);
	base = "0123456789abcdef";
	num1 = number;
	while (num1 >= 16)
	{
		temp[i] = base[num1 % 16];
		num1 = num1 / 16;
		i++;
	}
	temp[i] = base[num1 % 16];
	temp[i + 1] = '\0';
	return (temp);
}

char *l_e_loop_sequence(char *srt, t_data *data)
{
	char *temp;

	temp = expand_next_part(srt, data);
	free(srt);
	temp = quote_cutter(temp, 0, 0);
	return (temp);
}

t_tok	*only_heredoc(t_data *data, t_cmds	*temp_c)
{
	t_tok	*temp_t;

	temp_t = NULL;
	if (count_commands(data) == 1)
		exit(EXIT_SUCCESS);
	remove_node_c(&data->cmds, temp_c);
	return (temp_t);
}

static t_tok	*l_e_l_norm(t_tok *temp_t, t_cmds	*temp_c, t_data *data, char *name)
{
	t_tok	*temp_t2;

	if (ft_strncmp((temp_t)->content, "<<", 2))
	{
		(temp_t)->content = l_e_loop_sequence((temp_t)->content, data); //leak danger
		temp_t = (temp_t)->next;
	}
	else
	{
		unlink(name); // if multiple heredoc in one command it always start with clean file... need separate name for separate commands problem
		temp_t2 = temp_t->next->next;
		temp_t = (temp_t)->next;
		// (temp_t)->infile = here_doc(quote_cutter((temp_t)->content, 0, 0), data, name); // orogonoal
		temp_c->infile = here_doc(quote_cutter((temp_t)->content, 0, 0), data, name);
		if (count_tokens(temp_c) == 2)
			temp_t = only_heredoc(data, temp_c);
		else
		{
			remove_node(&temp_c->tokens, (temp_t)->prev); // freeeing content is not working... is it a leak???
			remove_node(&temp_c->tokens, (temp_t));
			temp_t = temp_t2;
		}
	}
	return (temp_t);
}

void	link_expand_looper(t_data *data)
{
	t_tok	*temp_t;
	t_cmds	*temp_c;
	char	*name;

	temp_t = data->cmds->tokens;
	temp_c = data->cmds;
	while (temp_c != NULL)
	{
		name = hd_name_maker((unsigned long)temp_c); // one more shit to free...
		temp_t = temp_c->tokens;
		while (temp_t != NULL)
		{
			temp_t = l_e_l_norm(temp_t, temp_c, data, name);
		}
		temp_c = temp_c->next;
	}
}


void data_load(char *temp, t_data *data)
{
	input_one_lilist(temp, data);


}