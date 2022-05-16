#include "ft_getopt.h"
#include "defines.h"

int visint(char *val)
{
	for (int i = 0; val[i]; i++)
		if (!('0' <= val[i] && val[i] <= '9'))
			return 0;
	return 1;
}

static void init_help(t_option *option)
{
	option->name = NULL;
	option->short_name = 'h';
	option->description = "Display this help message and exit.";
	option->need_value = 0;
	option->check = NULL;
	option->value = NULL;
	option->flag = OPT_H;
}

static void init_v(t_option *option)
{
	option->name = NULL;
	option->short_name = 'v';
	option->description = "Verbose output.";
	option->need_value = 0;
	option->value = NULL;
	option->check = NULL;
	option->flag = OPT_V;
}

static void init_t(t_option *option)
{
	option->name = NULL;
	option->short_name = 't';
	option->description = "Set TTL in seconds.";
	option->need_value = 1;
	option->check = visint;
	option->arg_help = "Needs an integer to set the TTL.";
	option->value = NULL;
	option->flag = OPT_T;
}

t_option *init_options(int *nb)
{
	*nb = 3;
	if (!*nb)
		return NULL;
	t_option *options = malloc(sizeof(t_option) * *nb);
	if (!options)
		return NULL;
	init_help(&options[0]);
	init_v(&options[1]);
	init_t(&options[2]);

	return options;
}
