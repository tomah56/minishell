#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include "../libs/libft/libft.h"

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
	DOLLARQ = 7,
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
	// needs to save all fd is not enoguh to update always the latest one.
	int				infile;  // execution order issue
	int				outfile;	// 
// bash-3.2$ < temp.txt <<  end wc
// > j
// > end
// bash: temp.txt: Permission denied
// bash-3.2$ chmod 0666 temp.txt 
// bash-3.2$ 
	struct s_token_data	*next;
	struct s_token_data	*prev;
}	t_tok;

typedef struct s_cmds
{
	t_tok			*tokens;
	int				infile;
	int				outfile;
	int				comandcount; //number of tokens per command
	int				heredocfile;
	bool			builtin;
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
	char	**paths;  //dont create paths at the beginning just right before execve, bc path can be changed!
}	t_data;

typedef struct s_size
{
	int ori;
	int len;
	int sta;
	int i;
	int j;
}	t_s;

extern int	g_exit;

// input
char	*get_next_line(int fd);
int		input_one_array(char *str, t_tok *tokdat, int i, int j);
void	input_one_lilist(char *str, t_data *data);
int		input_two(t_tok *tokdat);
//test
void	looper_next(t_data *data, void (*f)(char *));
char	*quote_cutter(char *str, int qusig, int qudou);
void	commands_link_to_array_looper(t_data *data);
char	*expand_clean_dollar(char *str, t_data *data);
int		size_dollar_point(char **str, t_data *data);
char	*expand_dirt_dollar(char *str, t_data *data);
void	check_token_flags_li(char str, t_data *data);
char	*expand_looper(char *str, t_data *data);
char	*expand_next_part(char *str, t_data *data);
void	link_expand_looper(t_data *data);


//here_doc
int	here_doc(char *stop, t_data * data);

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
int		count_commands(t_data	*data);
void	remove_node(t_tok **head, t_tok *node_to_remove); //nottest
void	remove_node_c(t_cmds **head, t_cmds *node_to_remove);

// builtins
void	builtin_env(t_data *data);
void	builtin_pwd(t_data *data);
void	builtin_export(t_data *data);
void	export_only(t_data *data);
void	save_variable_in_environ(t_data *data, char **command);
char	**sort_env(char **env);
void	print_export(t_data *data, char **exp);
void	builtin_cd(t_data *data);
void	cd_only(t_data *data);
char	*get_home(t_data *data);
void	change_var_env(t_data *data, char *var_name, char *new_var);
void	builtin_unset(t_data *data);
int		check_valid_var(t_data *data, char **command);
char	**delete_var_env(t_data *data, char **command, int i, int j);
void	builtin_exit(t_data *data);
void	builtin_echo(t_data *data);
void	check_for_builtins(t_data *data);
void	execute_builtin(t_data *data);

#endif