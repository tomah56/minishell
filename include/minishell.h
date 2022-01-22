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
	int qudouble;
	int qusingle;
	int reout;
	int reinp;
	int pipe;
	

}	t_p;

char	*get_next_line(int fd);
int		input_one(char *str);

#endif