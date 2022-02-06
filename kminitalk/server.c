#include "server.h"

int	g_global = SETSTART;

static void	send_back(int pidnum, int sucsess)
{
	if (sucsess == 1)
		kill(pidnum, 31);
	else
		kill(pidnum, 30);
}

static void	set_recived(int pidnums, int count)
{
	static int	get_pid;

	if (count == SETSTART)
		get_pid = 0;
	else if (count == MAKENUM)
	{
		get_pid *= 10;
		get_pid += pidnums - 48;
	}
	else if (count == FINNUM)
		g_global = FINNUM;
	else if (count == SENDBACK)
	{
		send_back(get_pid, 1);
		get_pid = 0;
	}
}

static int	package_handle(int temp)
{
	if (temp != '$' && g_global == MAKENUM)
		set_recived(temp, MAKENUM);
	else if (temp == '$' && g_global == MAKENUM)
		set_recived(temp, FINNUM);
	else
	{
		write(STDOUT_FILENO, &temp, 1);
		if (temp == '\0')
		{
			g_global = MAKENUM;
			set_recived(temp, SENDBACK);
		}
	}
	return (7);
}

static void	test_sig(int num)
{
	static int	i;
	static int	temp;

	if (g_global == SETSTART)
	{
		i = 7;
		temp = 0;
		g_global = MAKENUM;
		set_recived(temp, SETSTART);
	}
	if (i > -1)
	{
		if (num == 31)
			temp |= 1 << i;
		i--;
	}
	if (i == -1)
	{
		i = package_handle(temp);
		temp = 0;
	}
}

int	main(void)
{
	signal(SIGUSR1, test_sig);
	signal(SIGUSR2, test_sig);
	simple_printf("%d\n", getpid());
	while (1)
		pause();
	return (0);
}
