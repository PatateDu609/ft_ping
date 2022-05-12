#include "ft_ping.h"

#include <stdio.h>

void throw_error(char *msg)
{
	fprintf(stderr, "ft_ping: %s\n", msg);
	exit(1);
}

void warn(char *msg)
{
	fprintf(stderr, "ft_ping: %s\n", msg);
}
