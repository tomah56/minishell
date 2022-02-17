<<<<<<< HEAD
#include "../include/minishell.h"

char *make_path(t_data *data, char *str)
{
	char	*path;
	int i;

	i = 0;
	while (data->paths[i])
	{
		path = ft_strjoin(data->paths[i], "/");
		path = ft_strjoin(path, str);
		if (access(path, F_OK) == SUCCESS)
			return (path);
		i++;
		free(path);
	}
	free(path);
	msg_exit(data, "command not found\n");
	return (NULL);
}

//heredoc
// void execute_the_ii(t_data *data)
// {
// 	int fd[2]; // fd[0] read // fd[1] write
// 	int childfd[2];
// 	int id;
// 	int id2;
// 	char **comands;
// 	save_paths(data);
// 	printf("OUT> %d\n", data->cmds->outfile);
// 	printf("IN> %d\n", data->cmds->infile);
// 	printf("OUT 2> %d\n", data->cmds->next->outfile);
// 	printf("IN 2> %d\n", data->cmds->next->infile);

// 	fd[READ] = 3;
// 	childfd[READ] = fd[READ];
// 	pipe(fd);
	
// 	childfd[WRITE] = fd[WRITE];

// 	// if -1 then is failed

// 	id = fork();
// 	if (id == CHILD)
// 	{
// 		close(fd[READ]);
// 		dup2(childfd[WRITE], STDOUT_FILENO);
// 		dup2(childfd[READ], STDIN_FILENO);
// 		close(childfd[READ]);
// 		close(childfd[WRITE]);
// 		// close(fd[data->cmds->infile]);
// 		execve(make_path(data, data->cmds->commands[0]), data->cmds->commands, data->environ);
// 	}
// 	else
// 	{
// 		close(childfd[READ]);
// 		close(childfd[WRITE]);
// 	}
// // we dont need an else the child is taken over by the execve

// 	childfd[READ] = fd[READ];

// 	// pipe(fd);
// 	childfd[WRITE] = fd[WRITE];

// 	id2 = fork();
// 	if (id2 == CHILD)
// 	{
// 		close(fd[READ]);
// 		dup2(childfd[WRITE], STDOUT_FILENO);
// 		dup2(childfd[READ], STDIN_FILENO);
// 		close(childfd[READ]);
// 		close(childfd[WRITE]);
// 		execve(make_path(data, data->cmds->next->commands[0]), data->cmds->next->commands, data->environ);
// 	}
// 	else
// 	{
// 		close(childfd[READ]);
// 		close(childfd[WRITE]);
// 	}

// 	// teh main process also has to be closed
// 	close(fd[READ]);
// 	close(fd[WRITE]);
// 	waitpid(id, NULL, 0);
// 	waitpid(id2, NULL, 0);
// }

// /heredoc
// void execute_the_ii(t_data *data)
// {
// 	int id;
// 	int id2;
// 	t_cmds	*temp_cmds;
// 	save_paths(data);
// 	if (dup2(data->cmds->infile, STDIN_FILENO) == -1)
// 		write(2, "ERROR\n", 6);

// 	temp_cmds = data->cmds;
// 	temp_cmds->infile = 3;
// 	if (temp_cmds->infile != 0 || temp_cmds->infile != 1)
// 		dup2(temp_cmds->infile, STDIN_FILENO);
// 	pipe(data->pipefd);
// 	id = fork();
// 	if (id == CHILD)
// 	{
// 		printf("HERE\n");
// 		close(data->pipefd[READ]);
// 		if (dup2(temp_cmds->infile, STDIN_FILENO) == -1)
// 			write(2, "ERROR\n", 6);
// 		if (temp_cmds != NULL)
// 			dup2(data->pipefd[WRITE], STDOUT_FILENO);
// 		else
// 		{
// 			dup2(temp_cmds->outfile, STDOUT_FILENO);
// 			close(data->pipefd[WRITE]);
// 		}
// 		execve(make_path(data, data->cmds->commands[0]), data->cmds->commands, data->environ);
// 	}
// 	close(data->pipefd[READ]);
// 	close(data->pipefd[WRITE]);

// 	temp_cmds = temp_cmds->next;
// 	if (temp_cmds->infile != 0 || temp_cmds->infile != 1)
// 		dup2(temp_cmds->infile, STDIN_FILENO);
// 	pipe(data->pipefd);
// 	id2 = fork();
// 	if (id2 == CHILD)
// 	{
// 		close(data->pipefd[READ]);
// 		if (dup2(temp_cmds->infile, STDIN_FILENO) == -1)
// 			write(2, "ERROR\n", 6);
// 		if (temp_cmds != NULL)
// 			dup2(data->pipefd[WRITE], STDOUT_FILENO);
// 		else
// 		{
// 			dup2(temp_cmds->outfile, STDOUT_FILENO);
// 			close(data->pipefd[WRITE]);
// 		}
// 		execve(make_path(data, data->cmds->next->commands[0]), data->cmds->next->commands, data->environ);
// 	}
// 	close(data->pipefd[READ]);
// 	close(data->pipefd[WRITE]);

// 	waitpid(id, NULL, 0);
// 	waitpid(id2, NULL, 0);
// }

// void execute_the_ii(t_data *data)
// {
// 	int id;
// 	int id2;
// 	t_cmds	*temp_cmds;
// 	save_paths(data);
// 	if (dup2(data->cmds->infile, STDIN_FILENO) == -1)
// 		write(2, "ERROR\n", 6);

// 	temp_cmds = data->cmds;
// 	while (temp_cmds != NULL)
// 	{
// 		if (temp_cmds->infile != 0 || temp_cmds->infile != 1)
// 			dup2(temp_cmds->infile, STDIN_FILENO);
// 		pipe(data->pipefd);
// 		id = fork();
// 		if (id == CHILD)
// 		{
// 			close(data->pipefd[READ]);
// 			if (dup2(temp_cmds->infile, STDIN_FILENO) == -1)
// 				write(2, "ERROR\n", 6);
// 			if (temp_cmds != NULL)
// 				dup2(data->pipefd[WRITE], STDOUT_FILENO);
// 			else
// 			{
// 				dup2(temp_cmds->outfile, STDOUT_FILENO);
// 				close(data->pipefd[WRITE]);
// 			}
// 			execve(make_path(data, data->cmds->commands[0]), data->cmds->commands, data->environ);
// 		}
// 	}
// 	close(3);
// 	close(data->pipefd[READ]);
// 	close(data->pipefd[WRITE]);
// 	waitpid(id, NULL, 0);
// }

// Normal case onlly pipe
// void execute_the_ii(t_data *data)
// {
// 	int fd[2]; // fd[0] read // fd[1] write
// 	int id;
// 	int id2;
// 	char **comands;
// 	save_paths(data);



// 	pipe(fd);
// 	// if -1 then is failed


// 	id = fork();
// 	if (id == CHILD)
// 	{
// 		dup2(fd[WRITE], STDOUT_FILENO);
// 		close(fd[READ]);
// 		close(fd[WRITE]);
// 		execve(make_path(data, data->cmds->commands[0]), data->cmds->commands, data->environ);
// 	}
// // we dont need an else the child is taken over by the execve

// 	id2 = fork();
// 	if (id2 == CHILD)
// 	{
// 		dup2(fd[READ], STDIN_FILENO);
// 		close(fd[READ]);
// 		close(fd[WRITE]);
// 		execve(make_path(data, data->cmds->next->commands[0]), data->cmds->next->commands, data->environ);
// 	}

// 	// teh main process also has to be closed
// 	close(fd[READ]);
// 	close(fd[WRITE]);
// 	waitpid(id, NULL, 0);
// 	waitpid(id2, NULL, 0);
=======
#include "../include/minishell.h"

char *make_path(t_data *data, char *str)
{
	char	*path;
	int i;

	i = 0;
	while (data->paths[i])
	{
		path = ft_strjoin(data->paths[i], "/");
		path = ft_strjoin(path, str);
		if (access(path, F_OK) == SUCCESS)
			return (path);
		i++;
		free(path);
	}
	free(path);
	msg_exit(data, "command not found\n");
	return (NULL);
}

//heredoc
// void execute_the_ii(t_data *data)
// {
// 	int fd[2]; // fd[0] read // fd[1] write
// 	int childfd[2];
// 	int id;
// 	int id2;
// 	char **comands;
// 	save_paths(data);
// 	printf("%d\n", data->cmds->outfile);
// 	printf("%d\n", data->cmds->infile);

// 	fd[READ] = data->cmds->infile;
// 	childfd[READ] = fd[READ];
// 	pipe(fd);
	
// 	childfd[WRITE] = fd[WRITE];

// 	// if -1 then is failed

// 	id = fork();
// 	if (id == CHILD)
// 	{
// 		// close(fd[READ]);
// 		dup2(childfd[WRITE], STDOUT_FILENO);
// 		dup2(childfd[READ], STDIN_FILENO);
// 		close(childfd[READ]);
// 		close(childfd[WRITE]);
// 		// close(fd[data->cmds->infile]);
// 		execve(make_path(data, data->cmds->commands[0]), data->cmds->commands, data->environ);
// 	}
// 	else
// 	{
// 		// close(childfd[READ]);
// 		close(childfd[WRITE]);
// 	}
// // we dont need an else the child is taken over by the execve

// 	childfd[READ] = fd[READ];

// 	// pipe(fd);
// 	childfd[WRITE] = fd[WRITE];

// 	id2 = fork();
// 	if (id2 == CHILD)
// 	{
// 		close(fd[READ]);
// 		dup2(childfd[WRITE], STDOUT_FILENO);
// 		dup2(childfd[READ], STDIN_FILENO);
// 		close(childfd[READ]);
// 		close(childfd[WRITE]);
// 		execve(make_path(data, data->cmds->next->commands[0]), data->cmds->next->commands, data->environ);
// 	}
// 	else
// 	{
// 		close(childfd[READ]);
// 		close(childfd[WRITE]);
// 	}

// 	// teh main process also has to be closed
// 	close(fd[READ]);
// 	close(fd[WRITE]);
// 	waitpid(id, NULL, 0);
// 	waitpid(id2, NULL, 0);
// }

// /heredoc
void execute_the_ii(t_data *data)
{
	int fd[2]; // fd[0] read // fd[1] write
	int childfd[2];
	int id;
	int id2;
	char **comands;
	save_paths(data);

	pipe(fd);
	

	// if -1 then is failed


	id = fork();
	if (id == CHILD)
	{
		close(fd[READ]);
		dup2(data->cmds->infile, STDIN_FILENO);
		close(fd[data->cmds->infile]);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		execve(make_path(data, data->cmds->commands[0]), data->cmds->commands, data->environ);
	}
// we dont need an else the child is taken over by the execve

	id2 = fork();
	if (id2 == CHILD)
	{
		close(fd[WRITE]);
		dup2(fd[READ], STDIN_FILENO);
		close(fd[READ]);
		execve(make_path(data, data->cmds->next->commands[0]), data->cmds->next->commands, data->environ);
	}

	// teh main process also has to be closed
	close(fd[data->cmds->infile]);
	close(fd[READ]);
	close(fd[WRITE]);
	waitpid(id, NULL, 0);
	waitpid(id2, NULL, 0);
}

// Normal case onlly pipe
// void execute_the_ii(t_data *data)
// {
// 	int fd[2]; // fd[0] read // fd[1] write
// 	int id;
// 	int id2;
// 	char **comands;
// 	save_paths(data);



// 	pipe(fd);
// 	// if -1 then is failed


// 	id = fork();
// 	if (id == CHILD)
// 	{
// 		dup2(fd[WRITE], STDOUT_FILENO);
// 		close(fd[READ]);
// 		close(fd[WRITE]);
// 		execve(make_path(data, data->cmds->commands[0]), data->cmds->commands, data->environ);
// 	}
// // we dont need an else the child is taken over by the execve

// 	id2 = fork();
// 	if (id2 == CHILD)
// 	{
// 		dup2(fd[READ], STDIN_FILENO);
// 		close(fd[READ]);
// 		close(fd[WRITE]);
// 		execve(make_path(data, data->cmds->next->commands[0]), data->cmds->next->commands, data->environ);
// 	}

// 	// teh main process also has to be closed
// 	close(fd[READ]);
// 	close(fd[WRITE]);
// 	waitpid(id, NULL, 0);
// 	waitpid(id2, NULL, 0);
>>>>>>> 8404107a3028bac01db4c43abc965d55b0bfe479
// }