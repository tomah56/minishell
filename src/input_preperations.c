
#include "../include/minishell.h"

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
            // if (!ft_strncmp(temp_t->content, ">", 1))
                // data->
			temp = expand_next_part(temp_t->content, data);

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