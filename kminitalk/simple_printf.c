#include "server.h"
#include "client.h"

static int	pbe(long num, char *base, int devide, int count)
{
	if (num >= devide)
	{
		count = pbe(num / devide, base, devide, count + 1);
		num = num % devide;
	}
	if (num < devide)
		write(1, &base[num], 1);
	return (count);
}

static int	stringpritn(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!(str))
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i] != '\0')
	{
		count += write(1, &str[i], 1);
		i++;
	}
	return (count);
}

static int	crossroad(va_list args, char *quote)
{
	int	count;
	int	number;

	count = 0;
	if (*quote == 's')
		count += stringpritn(va_arg(args, char *));
	else if (*quote == 'd')
	{
		number = va_arg(args, int);
		if (number < 0)
		{
			count += write(1, "-", 1);
			number *= -1;
		}
		count += pbe(number, "0123456789", 10, 1);
	}
	else if (*quote == 'x')
		count += pbe(va_arg(args, unsigned int), "0123456789abcdef", 16, 1);
	return (count);
}

static int	is_valid(va_list args, char *quote)
{
	int	count;

	count = 0;
	while (*quote)
	{
		if (*quote == '%')
		{
			quote++;
			if (*quote == 's' || *quote == 'd' || *quote == 'x')
			{
				count += crossroad(args, quote);
			}
			else
				count += write(1, quote, 1);
		}
		else
			count += write(1, quote, 1);
		quote++;
	}
	return (count);
}

int	simple_printf(char *quote, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, quote);
	count += is_valid(args, quote);
	va_end(args);
	return (count);
}
