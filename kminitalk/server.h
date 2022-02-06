#ifndef SERVER_H
# define SERVER_H

// simpleprint
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

// signals
# include <signal.h>

enum e_signs
{
	SETSTART,
	MAKENUM,
	FINNUM,
	SENDBACK
};

int	simple_printf(char *quote, ...);

#endif