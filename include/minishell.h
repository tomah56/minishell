#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include "../libs/libft/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_token_data
{
	// char *commandlist;
	char **tokensfull;
	int tokencount;
	int qudouble;
	int qusingle;
	int reout;
	int reinp;
	int pipe;


}	t_tok;

typedef struct s_data
{
	char	**environ;
	char	**paths;
	t_tok	*tokdat;
}	t_data;

// input
char	*get_next_line(int fd);
int		input_one(char *str, t_tok *tokdat, int i, int j);
int		input_two(t_tok *tokdat);

// sonja
void	create_environment(t_data *data, char **env);
void	msg_exit(t_data *data, char *msg);
void	free_struct(t_data *data);

#endif