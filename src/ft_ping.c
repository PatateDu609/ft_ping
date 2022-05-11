#include "ft_ping.h"
#include <stdio.h>

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

	int r = getaddrinfo(name, NULL, &hint, &res);
	printf("getaddrinfo res = %d\n", r);
	return res;
}

void ping(t_args *args)
{
	t_data *data = malloc(sizeof(t_data));

	if (!data)
		throw_error("Allocation failed");

	data->args = args;
	data->infos = resolve_addr(args->args[0]);
}