#include "../../include/minishell.h"

static unsigned int	freover(char *copy, char *temp, unsigned int caunt)
{
	free(temp);
	free(copy);
	return (caunt + 1);
}

static unsigned int	recurlen(char const *s, char *ref)
{
	unsigned int	i;
	char			*copy;
	char			*temp;
	unsigned int	caunt;

	temp = (char *)s;
	caunt = 0;
	copy = ft_strtrim(temp, ref);
	while (copy[0] != '\0')
	{
		i = 0;
		while (copy[i] != ref[0] && copy[i] != '\0')
			i++;
		if (caunt > 0)
			free(temp);
		temp = ft_substr(copy, i, (ft_strlen(copy) - i));
		if (temp[0] == '\0')
			return (freover(copy, temp, caunt));
		free(copy);
		copy = ft_strtrim(temp, ref);
		caunt++;
	}
	free(copy);
	return (caunt);
}

static void	rec(char const *s, char *ref, char **result, unsigned int index)
{
	unsigned int	i;
	char			*copy;
	char			*subcopy;

	copy = ft_strtrim(s, ref);
	i = 0;
	while (copy[i] != ref[0] && copy[i] != '\0')
		i++;
	if (copy[0] != '\0')
	{
		subcopy = ft_substr(copy, i, (ft_strlen(copy) - i));
		result[index] = ft_substr(copy, 0, i);
		rec(subcopy, ref, result, index + 1);
		free(subcopy);
	}
	free(copy);
}

char	**plus_split(char const *s, char c)
{
	char			**arrayofstrings;
	unsigned int	piece;
	char			*ref;

	if (s == NULL)
		return (NULL);
	ref = malloc(2 * sizeof(char));
	if (!ref)
		return (NULL);
	ref[0] = c;
	ref[1] = '\0';
	piece = 2;
	piece = recurlen(s, ref);
	arrayofstrings = (char **)malloc((piece + 1) * sizeof(char *));
	if (arrayofstrings == NULL)
		return (NULL);
	arrayofstrings[piece] = "./";
	arrayofstrings[piece + 1] = NULL;
	if (piece > 0)
		rec(s, ref, arrayofstrings, 0);
	free (ref);
	return (arrayofstrings);
}
