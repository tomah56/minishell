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
	RED_IN = 3,  //  <
	RED_OUT_TRUNC = 4, //  >
	HEREDOC = 5, //  <<
	RED_OUT_APPEND = 6,//  >>
	NOQUOTE = 0,
	QUSINGLE = 1,
	QUDOUBLE = 2,
	FAILED = -1,
	SUCCESS = 0,
};

typedef struct s_token_data
{
	char **tokensfull; //* { *echo, * chello, *other}
	int qudouble;
	int qusingle;
	int tokencount;

	int					type;
	char				*content;// *echo ---- > *conent hello  ---- > *content aother
	int					quote_type;
	struct s_token_data	*next;
	struct s_token_data	*prev;
}	t_tok;

typedef struct s_cmds
{
	t_tok			*tokens;
	int				infile;
	int				outfile;
	int				comandcount; //number of tokens per command
	int				heredocon;
	char			**commands; // not sure the functinality here ? ->this will be the string we have to give execve (we create it after parsing)
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

typedef struct s_data
{
	t_cmds	*cmds;
	t_cmds	*actual; 	//keeps track of current command -> when going to the next cmd always do cmds->next
	int qudouble;
	int qusingle;
	int tokentotal;
	int tokencount;
	int i;
	int j;
	int k;
	t_cmds	*normcm;
	t_tok	*normtok;
	char	**environ;
	char	**paths;
}	t_data;

// input
char	*get_next_line(int fd);
int		input_one_array(char *str, t_tok *tokdat, int i, int j);
void	input_one_lilist(char *str, t_data *data);
int		input_two(t_tok *tokdat);
//test
void	looper_next(t_data *data, void (*f)(char *));
char	*quote_cutter(char *str, int qusig, int qudou);
void	commands_link_to_array_looper(t_data *data);

// sonja
void	create_environment(t_data *data, char **env);
void	msg_exit(t_data *data, char *msg);
void	free_struct(t_data *data);
void	save_paths(t_data *data, char **env);

// linked list functions
t_cmds	*create_new_cmds_node(t_tok *tokdat, int count);
t_tok	*create_new_token_node(char *str);
void	add_token_node_at_back(t_tok **list, t_tok *newnode);
void	add_cmds_node_at_back(t_cmds **list, t_cmds *newnode);
int		count_tokens(t_cmds	*data);

// builtins
void	builtin_env(t_data *data);
void	builtin_pwd(t_data *data);
void	builtin_export(t_data *data);
void	export_only(t_data *data);
void	save_variable_in_environ(t_data *data, char **command);
char	**sort_env(char **env);
void	builtin_cd(t_data *data);
void	cd_only(t_data *data);
char	*get_home(t_data *data);
void	change_var_env(t_data *data, char *var_name, char *new_var);
void	builtin_unset(t_data *data);
int		check_valid_var(t_data *data, char **command);
char	**delete_var_env(t_data *data, char **command, int i, int j);

#endif