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


static void	l_e_l_norm(t_tok **temp_t, t_cmds	*temp_c, t_data *data, char *name)
{
	if (ft_strncmp((*temp_t)->content, "<<", 2))
	{
		(*temp_t)->content = l_e_loop_sequence((*temp_t)->content, data); //leak danger
		*temp_t = (*temp_t)->next;
	}
	else
	{
		unlink(name); // if multiple heredoc in one command it always start with clean file... need separate name for separate commands problem
		(*temp_t)->bedeleted = 1;
		*temp_t = (*temp_t)->next;
		(*temp_t)->bedeleted = 1;
		(*temp_t)->infile = here_doc(quote_cutter((*temp_t)->content, 0, 0), data, name); // original
		// temp_c->infile = here_doc(quote_cutter((*temp_t)->content, 0, 0), data, name); // direct save for test
	}
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
			(temp_t)->bedeleted = 0;
			(temp_t)->infile = -1;
			(temp_t)->outfile = -1;
			l_e_l_norm(&temp_t, temp_c, data, name);
		}
		temp_c = temp_c->next;
	}
}


void data_load(char *temp, t_data *data)
{
	input_one_lilist(temp, data);
}