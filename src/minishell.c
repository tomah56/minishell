#include "../include/minishell.h"



int	main(int argc, char **argv, char **envp)
{
	t_p	stone;
	char *temp;
	// char 
	// write(1,"minishe master$ ", 16);
	// execve("/usr/bin/grep", &argv[1], envp);
	temp = "not";
	while (temp)
	{
		temp = readline("minishe master$ ");
		if (!ft_strncmp(temp, "exit", 5))
		{
			free(temp);
			temp = NULL;
		}
		else
		{
			input_one(temp);
			printf("%s\n", temp);
		}
	}
	// sorting_game(&stone);

	return (0);
}