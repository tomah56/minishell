#include "../include/minishell.h"

void h_doc_to_file(int fd, char *str)
{
	
	if (fd == -2)
		fd = open("temp.txt", O_WRONLY | O_CREAT | O_APPEND/* , 0644 */);
	else
	{
		write(fd, &str, ft_strlen(str));
		write(fd, "\n", 1);
	}
}

char	*here_doc_to_string(char *stop, t_data * data)
{
	char	*temp;
	char	*superholder;
	int		size;

	if (stop == NULL)
		return (NULL); // bash: syntax error near unexpected token `newline'
	superholder = NULL;
	size = ft_strlen(stop);
	temp = readline(">");
	while (ft_strncmp(temp, stop, size) || temp[size] != '\0')
	{
		if (superholder == NULL)
		{
			superholder = ft_strdup(temp);
		}
		else
			superholder = ft_strjoin(superholder, temp);
			//question should we save the new lines too???? curently it oes not do that
			//also maybe is not enough to save it in a string it needs a file descriptor?
		temp = readline(">");
	}
	return (superholder);
}

int	here_doc(char *stop, t_data * data)
{
	char	*temp;
	int		size;
	int fd;

	if (stop == NULL)
	{
		write(2, "ERROR\n",6);
		return (-1); // bash: syntax error near unexpected token `newline'
	}
	fd = open("temp.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == FAILED)
	{
		write(2, "ERROR\n",6); // temperarrly
		return (-1);
	}
	size = ft_strlen(stop);
	temp = readline(">"); // how is this gets inside my linked list????????
	while (ft_strncmp(temp, stop, size) || temp[size] != '\0')
	{
		temp = no_expand_next_part_no(temp, data);
		write(fd, temp, ft_strlen(temp));
		write(fd, "\n", 1);
		temp = readline(">");
	}
	close(fd);
	return (fd);
}

// heredoc scpeials
// bash-3.2$ << he grep b
// > b
// > b
// > he
// b
// b
// bash-3.2$ echo bobo << he grep b
// > b
// > s
// > he
// bobo grep b
// bash-3.2$ 
