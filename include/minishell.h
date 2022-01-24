#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include "../libs/libft/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

//signals
# include <signal.h>

enum e_enum
{
	WORD = 1,
	METACHAR = 2,
	RED_IN = 3,
	RED_OUT_TRUNC = 4,
	HEREDOC = 5,
	RED_OUT_APPEND = 6,
	NOQUOTE = 0,
	QUSINGLE = 1,
	QUDOUBLE = 2,
	FAILED = -1,
};

typedef struct s_token_data
{
	char **tokensfull;
	int tokencount;
	int qudouble;
	int qusingle;

	int					type;
	char				*content;
	int					quote_type;
	struct s_token_data	*next;
	struct s_token_data	*prev;
}	t_tok;

typedef struct s_cmds
{
	t_tok			*tokens;
	int				infile;
	int				outfile;
	char			**commands; // not sure the functinality here ? ->this will be the string we have to give execve (we create it after parsing)
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

typedef struct s_data
{
	t_cmds	*cmds;
	int qudouble;
	int qusingle;
	char	**environ;
	char	**paths;
}	t_data;




// input
char	*get_next_line(int fd);
int		input_one_array(char *str, t_tok *tokdat, int i, int j);
int		input_one_lilist(char *str, t_data *data, int i, int j);
int		input_two(t_tok *tokdat);

// sonja
void	create_environment(t_data *data, char **env);
void	msg_exit(t_data *data, char *msg);
void	free_struct(t_data *data);
void	save_paths(t_data *data, char **env);

// linked list functions
t_cmds	*create_new_cmds_node(t_data *data);
t_tok	*create_new_token_node(char *str);
void	add_token_node_at_back(t_tok **list, t_tok *newnode);

#endif