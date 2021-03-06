#include <stdio.h>
#include "ft_getopt.h"
#include "utils.h"
#include "ft_ping.h"
#include "random.h"

void print_help(t_args *args)
{
	printf("Usage: ./ft_ping [OPTION]... ADDRESS\n");
	for (int i = 0; i < args->nb_opt; i++)
	{
		printf("\n");
		printf("\033[1;31m-%c\033[0m", args->options[i].short_name);
		if (args->options[i].name)
			printf(", --%s", args->options[i].name);
		if (args->options[i].need_value && args->options[i].small_print)
			printf("\t\033[1;32m%s\033[0m", args->options[i].small_print);
		printf("\n\t%s\n", args->options[i].description);
	}
}

int main(int argc, char **argv)
{
	t_args *arg_opt = parse_args(argc, argv);

	if (!arg_opt || arg_opt == (void *)-1)
		return 1;

	if (arg_opt->flags & OPT_H)
	{
		print_help(arg_opt);
		free_args(arg_opt);
		return 0;
	}

	char *name = arg_opt->args[0];

	if (!name || arg_opt->args[1])
	{
		print_help(arg_opt);
		return 1;
	}

	init_pcg_state();
	ping(arg_opt);

	return 0;
}
