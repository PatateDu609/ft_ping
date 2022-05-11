#include "ft_getopt.h"
#include "defines.h"

static void init_help(t_option *option)
{
	option->name = "help";
	option->short_name = 'h';
	option->description = "Display this help message and exit.";
	option->value = NULL;
	option->flag = OPT_H;
}

static void init_v(t_option *option)
{
	option->name = "verbose";
	option->short_name = 'v';
	option->description = "Verbose output.";
	option->value = NULL;
	option->flag = OPT_V;
}

t_option *init_options(int *nb)
{
	*nb = 2;
	if (!*nb)
		return NULL;
	t_option *options = malloc(sizeof(t_option) * *nb);
	if (!options)
		return NULL;
	init_help(&options[0]);
	init_v(&options[1]);

	return options;
}
