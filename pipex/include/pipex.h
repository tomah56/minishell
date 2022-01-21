/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:41:17 by sreinhol          #+#    #+#             */
/*   Updated: 2021/12/26 22:12:42 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
}	t_enum;

typedef struct s_pipex
{
	char	**paths;
	char	*path1;
	char	*path2;
	int		pipe[2];
	int		fdin;
	int		fdout;
	char	**cmd1;
	char	**cmd2;
}t_pipex;

void		input_check(int argc, char **argv, t_pipex *pipex);
void		save_path(char **argv, t_pipex *pipex, char **envp);

void		child_1_process(t_pipex *pipex, char **envp);
void		child_2_process(t_pipex *pipex, char **envp);

void		close_pipes(t_pipex *pipex);
int			error_msg(char *error);
void		error(char *error);
void		check_init_error(t_pipex *pipex);

void		free_cmd1(t_pipex *pipex);
void		free_cmd2(t_pipex *pipex);
void		free_paths(t_pipex *pipex);
void		free_struct(t_pipex *pipex);
#endif
