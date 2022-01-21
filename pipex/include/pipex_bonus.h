/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:41:17 by sreinhol          #+#    #+#             */
/*   Updated: 2021/12/27 12:44:26 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>

# include "../../libs/libft/libft.h"

typedef enum e_enum
{
	FAILED = -1,
	SUCCESS = 0,
	READ = 0,
	WRITE = 1,
	CHILD = 0,
	FIRST = 4,
	MIDDLE = 5,
	LAST = 6,
}	t_enum;

typedef struct s_pipex
{
	char	**paths_cmd;
	char	*path_envp;
	int		childfd[2];
	int		pipefd[2];
	int		heredoc;
	int		childs;
	int		nbr_pipes;
}t_pipex;

void		input_check(int argc, char **argv, t_pipex *pipex);
void		save_path(t_pipex *pipex, char **envp);
void		pipes(t_pipex *pipex, int flag, char **argv, int argc);

int			here_doc(char *limiter);
void		here_doc_helper(char *limiter, int *fd);

void		execute_cmd(t_pipex *pipex, char *cmd, char **envp);
void		process_creator(t_pipex *pipex, char *cmd, char **envp);

int			error_msg(char *error);
void		error(char *error);

void		free_paths(t_pipex *pipex);

char		*get_next_line(int fd);
char		*read_loop(int fd, char *line, char *save, int rread);
char		*ft_linejoin(char const *s1, char const *s2);
char		*ft_substr_gnl(char *s, unsigned int start, size_t len);
char		*ft_free(char *line);
char		line_end(char *s);
int			line_len(char *save);
#endif
