#include "../include/minishell.h"

static int	chekker(int size, char **strn, t_p *stone)
{
	int		*temp;
	int		i;

	i = 0;
	while (i < size)
	{
		// if (!ft_strncmp(strn[i], "echo", 5))
		// {
		// 	i++;
		// 	printf("\nafter echo; %s\n", strn[i]);
		// }
		// else
		// {
		// 	printf("else: %s ", strn[i]);
		// i++;
		// }
			printf("%s ", strn[i]);
			i++;

	}
	// write(1, "\n",1);

	return (1);
}

static int	cut_short(char *argv, t_p *stone)
{
	char	**temp;
	int		size;

	size = 0;
	temp = ft_split(argv, ' ');
	while (temp[size] != NULL)
		size++;
	if (size < 1)
		return (0);
	return (chekker(size, temp, stone));
}

int	main(int argc, char **argv)
{
	int	check;
	int	i;
	t_p	stone;

	i = 1;
	
	if (argc > 1)
	{
		while (i < argc)
		{
			check = cut_short(argv[i], &stone);
			i++;
		}
	}
	else
		check = 0;
	if (check == 0)
	{
 		write(STDERR_FILENO, "Error\n", 6);
		return (0);
	}

	return (0);
}