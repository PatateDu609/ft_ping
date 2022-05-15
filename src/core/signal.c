#include "ft_ping.h"
#include <signal.h>
#include <stdio.h>

static void sigquit()
{
	print_stats(0);
}

static void sigint()
{
	dprintf(1, "\b\b");
	print_stats(1);
	exit(0);
}

void ft_sighandler(int sig)
{
	if (sig == SIGINT)
		sigint();
	else if (sig == SIGQUIT)
		sigquit();
}
