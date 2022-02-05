#include "../include/minishell.h"

char	*here_doc(char *stop, t_data * data)
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
				free(temp);
			}
			else
				superholder = ft_strjoin(superholder, temp);
				//question should we save the new lines too???? curently it oes not do that
				//also maybe is not enough to save it in a string it needs a file descriptor?
			temp = readline(">");
	}
	return (superholder);
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
