#include "../include/minishell.h"


void sorting_game(t_p *stone)
{
	char *buf;

	buf = get_next_line(0);
	while (buf)
	{
		write(1,"minishe master$ ", 16);
		if (!ft_strncmp(buf, "echo", 4))
			printf("next: %s", buf + 4);
		else
			printf("%s", buf);

	
	
		buf = get_next_line(0);
		if (!ft_strncmp(buf, "q", 1))
		{
			free(buf);
			buf = NULL;
		}
	}
	if (buf != NULL)
		free(buf);
}

int	main(int argc, char **argv, char **envp)
{
	t_p	stone;
	char *test;
	// write(1,"minishe master$ ", 16);
	test = readline("minishe master$ ");
	while (test)
	{
		printf("%s\n", test);
		test = readline("minishe master$ ");
	}
	// sorting_game(&stone);

	return (0);
}