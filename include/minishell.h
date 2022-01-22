#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include "../libs/libft/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_stone
{
	char *commandlist;

}	t_p;

typedef struct s_data
{
	char	**environ;
	char	**paths;

}	t_data;

char	*get_next_line(int fd);
void	create_environment(t_data *data, char **env);
void	msg_exit(t_data *data, char *msg);
void	free_struct(t_data *data);

#endif