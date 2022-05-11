#include <stdio.h>
#include "ft_getopt.h"
#include "utils.h"
#include "ft_ping.h"

void print_help(t_args *args)
{
	printf("Usage: ./ft_ping [OPTION]... ADDRESS\n");
	for (int i = 0; i < args->nb_opt; i++)
	{
		printf("-%c, --%s\n", args->options[i].short_name, args->options[i].name);
		printf("\t%s\n", args->options[i].description);
	}
}

int main(int argc, char **argv)
{
	t_args *arg_opt = parse_args(argc, argv);

	if (!arg_opt || arg_opt == (void *)-1)
		return 1;

	char *name = arg_opt->args[0];

	if (!name || arg_opt->args[1])
	{
		print_help(arg_opt);
		return 1;
	}

	ping(arg_opt);

	return 0;
}
