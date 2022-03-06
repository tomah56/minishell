#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
// # include <std

#include "../libs/libft/libft.h"

// # include <readline.h>
// # include <history.h>
#include <readline/readline.h>
#include <readline/history.h>

// signals
#include <signal.h>

enum e_enum
{
	WORD = 1,
	METACHAR = 2,
	RED_IN = -1,			//  <
	RED_OUT_TRUNC = -2,	//  >
	HEREDOC = -3,		//  <<
	RED_OUT_APPEND = -4, //  >>
	PIPE = -8,
	NOQUOTE = 0,
	QUSINGLE = 1,
	QUDOUBLE = 2,
	DOLLARQ = 7,
	FAILED = -1,
	SUCCESS = 0,
	FIRST = 1,
	MIDDLE = 2,
	LAST = 3,
	READ = 0,
	WRITE = 1,
	CHILD = 0,
};

typedef struct s_token_data
{
	char				**tokensfull; //* { *echo, * chello, *other}
	int					qudouble;
	int					qusingle;
	int					tokencount;
	int					type;
	char				*content; // *echo ---- > *conent hello  ---- > *content aother
	int					quote_type;
	char				*hd_file;
	// needs to save all fd is not enoguh to update always the latest one.
	int					infile;	 // execution order issue
	int					outfile; //
	int					bedeleted;
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
	int				infile;		 // stdin
	int				outfile;	 // stdout /
	int				heredoc; //-10 its not a herdoc
	int				comandcount; // number of tokens per command
	int				heredocfile;
	bool			builtin;
	char			*defpath;
	char			*cm_hd_file; // unlink file after execution.
	int				type;
	bool			last;
	int				fail;
	char			**commands;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

typedef struct s_data
{
	t_cmds		*cmds;
	t_cmds		*actual;
	int			qudouble;
	int			qusingle;
	int			tokentotal;
	int			tokencount;
	int			dpflag;
	int			falg;
	int			i;
	int			j;
	int			k;
	// int			fdin;
	// int			fdout;
	int			fd[2];
	int			save_fd;
	pid_t		pid;
	char		**environ;
	char		**paths;
}	t_data;

typedef struct s_size
{
	int	ori;
	int	len;
	int	sta;
	int	i;
	int	j;
}	t_s;

extern int g_exit; // check this?

// input
char	*get_next_line(int fd);
// int		input_one_array(char *str, t_tok *tokdat, int i, int j); del
void	input_one_lilist(char *str, t_data *data);
// int		input_two(t_tok *tokdat);
// test
void	looper_next(t_data *data, void (*f)(char *));
char	*quote_cutter(char *str, int qusig, int qudou);
void	commands_link_to_array_looper(t_data *data);

char	*expand_clean_dollar(char *str, t_data *data);
void	check_token_flags_li(char str, t_data *data);
char	*expand_next_part(char *str, t_data *data);
void	link_expand_looper(t_data *data);
void	sytax_looper(t_data *data);
char	*slash_join(char const *s1, char const *s2);

// expand heredoc no quotes
char	*no_expand_next_part_no(char *str, t_data *data);

// here_doc
void	here_doc(char *stop, t_data *data, t_cmds *temp_c, t_tok **temp_t);
int		old_here_doc(char *stop, t_data *data, char *name);
void	del_temp_looper(t_data *data);

// redirections
void	bypass_juntion(t_data *data);
int		bypass_helper(t_tok **temp_t, t_cmds *temp_c, t_data *data, int fail);
int		red_outfile_trunc(t_data *data, t_cmds *temp_c, t_tok **temp_t);
int		red_outfile_append(t_data *data, t_cmds *temp_c, t_tok **temp_t);
int		red_infile(t_data *data, t_cmds *temp_c, t_tok **temp_t);

void	remove_linklist_file_looper(t_data *data);

// expands and then removes quotes
char	*l_e_loop_sequence(char *str, t_data *data);
// t_tok	*only_heredoc(t_data *data, t_cmds	*temp_c);
// setting the need to use infiels outfiles
void	in_out_file_looper(t_data *data);

// linked list functions
t_cmds	*create_new_cmds_node(t_tok *tokdat, int count);
t_tok	*create_new_token_node(char *str);
void	add_token_node_at_back(t_tok **list, t_tok *newnode);
void	add_cmds_node_at_back(t_cmds **list, t_cmds *newnode);
int		count_tokens(t_cmds *data);
int		count_commands(t_data *data);
void	remove_node(t_tok **head, t_tok *node_to_remove); // nottest
void	remove_node_c(t_cmds **head, t_cmds *node_to_remove);
// other version of remove node
void	ot_remove_node(t_tok **head, t_tok *node_to_remove);

// environment
void	create_environment(t_data *data, char **env);
void	save_paths(t_data *data);

//error + free
void	msg_exit(t_data *data, char *msg);
void	error_msg(char *msg);
void	error_msg_no(char *msg);
void	dup_exit(t_data *data, char *msg);
void	cmd_not_found_error(t_data *data, char *msg);
void	free_struct(t_data *data);
void	free_cmds_struct(t_cmds **cmds);
void	free_token_struct(t_tok **token);
void	ft_free_3array(char ***input);
void	ft_free_2array(void **to_free);

// builtins
void	builtin_env(t_data *data);
void	builtin_pwd(t_data *data);
void	builtin_export(t_data *data);
void	export_only(t_data *data);
void	save_variable_in_environ(t_data *data, char **command, int i);
char	**sort_env(char **env);
void	print_export(t_data *data, char **exp);
void	builtin_cd(t_data *data);
void	cd_only(t_data *data);
char	*get_home(t_data *data);
void	change_var_env(t_data *data, char *var_name, char *new_var);
void	builtin_unset(t_data *data);
int		check_valid_var(t_data *data, char **command);
void	delete_var_env(t_data *data, char **command, int i);
void	builtin_exit(t_data *data);
void	builtin_echo(t_data *data);
void	check_for_builtins(t_data *data);
void	builtins(t_data *data, t_cmds *cmds, int flag);
void	execute_builtin(t_data *data, t_cmds *cmds);
void	exec_builtins(t_data *data, t_cmds *cmds);

// execution
void	execute(t_data *data);
void	execute_cmd(t_data *data, t_cmds *temp_c, int i);
void	process_creator(t_data *data, t_cmds *temp_c, int cmd_count, int flag);
void	pipes(t_data *data, int flag, t_cmds *temp_c);
void	execute_one_cmd(t_data *data);
int		ft_dup(t_data *data, int fd);
void	ft_dup2(t_data *data, int fd1, int fd2);
void	ft_close(t_data	*data, int fd);
void	ft_pipe(t_data *data, int *fd);
void	ft_fork(t_data *data);

void	execute_the_ii(t_data *data);

// to delete later
void	printlist(t_data *data);
#endif