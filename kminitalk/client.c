#include "client.h"

static void	bin_decoder(int smile, int pidid)
{
	int	mu;
	int	i;

	i = 7;
	while (i > -1)
	{
		mu = ((smile >> i) & 1);
		usleep(15);
		if (mu == 0)
		{
			kill(pidid, 30);
		}
		else if (mu == 1)
		{
			kill(pidid, 31);
		}
		i--;
	}
}

static void	looper(char *msgstr, int pidid)
{
	int	i;

	i = 0;
	while (msgstr[i] != '\0')
	{
		bin_decoder(msgstr[i], pidid);
		i++;
	}
}

static void	pbe(int num, char *base, int pidid)
{
	if (num >= 10)
	{
		pbe(num / 10, base, pidid);
		num = num % 10;
	}
	if (num < 10)
		bin_decoder(base[num], pidid);
}

static void	rec_sig(int num)
{
	if (num == 31)
		write(1, "Message delivered\n", 18);
	else
		write(1, "Message failed\n", 16);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	long	pidid;

	signal(SIGUSR1, rec_sig);
	signal(SIGUSR2, rec_sig);
	if (argc == 3)
	{
		pidid = long_atoi(argv[1]);
		if (pidid < 1 || pidid > INT_MAX)
			return (0);
		pbe(getpid(), "0123456789", (int)pidid);
		looper("$", (int)pidid);
		looper(argv[2], (int)pidid);
		bin_decoder('\0', pidid);
	}
	else
	{
		write(1, "Wrong input\n", 12);
		return (0);
	}
	sleep(5);
	rec_sig(0);
	return (0);
}
