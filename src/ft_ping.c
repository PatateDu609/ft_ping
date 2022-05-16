#include "ft_ping.h"
#include <unistd.h>
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

	if (getaddrinfo(name, NULL, &hint, &res))
		throw_error("Error resolving address");
	return res;
}

static int32_t ft_atoi(char *str)
{
	int32_t res;
	int32_t sign;

	res = 0;
	sign = 1;
	while (*str == ' ')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return res * sign;
}

static int32_t ft_chk_opt(t_args *args, char opt)
{
	for (int32_t i = 0; i < args->nb_opt; i++)
	{
		if (args->options[i].short_name == opt && args->options[i].need_value)
		{
			if (!(args->flags & args->options[i].flag))
				return 0;
			switch (opt)
			{
			case 't':
			case 's':
			case 'c':
			case 'i':
				return ft_atoi(args->options[i].value);
			}
		}
	}
	return 0;
}

void ping(t_args *args)
{
	g_data = malloc(sizeof(t_data));

	if (!g_data)
		throw_error("Allocation failed");

	g_data->args = args;
	g_data->infos = resolve_addr(args->args[0]);
	g_data->seq = 1;

	g_data->size = ft_chk_opt(args, 's');
	g_data->ttl = ft_chk_opt(args, 't');
	g_data->count = ft_chk_opt(args, 'c');
	g_data->interval = ft_chk_opt(args, 'i');

	g_data->ttl = g_data->ttl ? g_data->ttl : 120;
	g_data->size = g_data->size ? g_data->size : 56;
	g_data->count = g_data->count ? g_data->count : -1;
	g_data->interval = g_data->interval ? g_data->interval : 1000;

	if (g_data->interval < 2 && getuid())
		throw_error("Interval must be greater than 2 for non root user");

	__ping(g_data);
}
