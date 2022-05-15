#include "ft_ping.h"
#include <stdio.h>

t_data *g_data = NULL;
static struct addrinfo *resolve_addr(char *name)
{
	struct addrinfo *res;
	struct addrinfo hint;

	hint.ai_addr = NULL;
	hint.ai_addrlen = 0;
	hint.ai_family = AF_INET;
	hint.ai_flags = AI_CANONNAME;
	hint.ai_protocol = 0;
	hint.ai_socktype = 0;

	getaddrinfo(name, NULL, &hint, &res);
	return res;
}

void ping(t_args *args)
{
	g_data = malloc(sizeof(t_data));

	if (!g_data)
		throw_error("Allocation failed");

	g_data->args = args;
	g_data->infos = resolve_addr(args->args[0]);
	g_data->size = 56;
	g_data->seq = 1;
	__ping(g_data);
	free(g_data);
}
