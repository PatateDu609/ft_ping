#include "ft_ping.h"
#include <signal.h>
#include <stdio.h>

static void sigquit()
{
	dprintf(1, "\b\b");
	print_stats(0);
}

static void sigint()
{
	printf("\n");
	print_stats(1);

	freeaddrinfo(g_data->infos);
	free_args(g_data->args);
	free(g_data);
	exit(0);
}

void ft_sighandler(int sig)
{
	if (sig == SIGALRM)
		return;
	if (sig == SIGINT)
		sigint();
	else if (sig == SIGQUIT)
		sigquit();
}
