#include "../../include/minishell.h"

void	sytax_looper(t_data *data)
{
	t_tok	*temp_t;
	t_cmds	*temp_c;

	temp_t = data->cmds->tokens;
	temp_c = data->cmds;
	data->dpflag = 0;
	while (temp_c != NULL)
	{
		temp_t = temp_c->tokens;
		// temp_c->defpath = ft_strjoin("./", temp_c->commands[0]); // not in the rigth place...  // version for inside the place
		temp_c->defpath = NULL;
		// while (temp_t != NULL)
		// {

		// }
		temp_c = temp_c->next;
	}
}

void	del_temp_looper(t_data *data)
{
	t_tok	*temp_t;
	t_cmds	*temp_c;

	temp_t = data->cmds->tokens;
	temp_c = data->cmds;
	data->dpflag = 0;
	while (temp_c != NULL)
	{
		temp_t = temp_c->tokens;
		// while (temp_t != NULL)
		// {

		// }
		if (temp_c->cm_hd_file != NULL)
			unlink(temp_c->cm_hd_file);
		temp_c = temp_c->next;
	}
}
