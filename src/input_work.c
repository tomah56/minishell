#include "../include/minishell.h"

int	input_one(char *str)
{
	int	i;
	char *metachar;
	char **toktemp;

	metachar = "$<>|'\"";
	i = 0;
	while (*str)
	{
		//malloc toktemp i
		// i_strchr("-0+ #", *quote) != -1
		// save the token there cahracter by caracter until the end. 
		// check end with special caracters to know f its the next one or what....;
		// toktemp[i] 
		// if (*str == '"')

		str++;
	}
	return (1);
}