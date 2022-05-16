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
	option->small_print = "TTL";
}

static void init_c(t_option *option)
{
	option->name = NULL;
	option->short_name = 'c';
	option->description = "Set the number of packets to send.";
	option->need_value = 1;
	option->check = visint;
	option->arg_help = "Needs an integer to set the number of packets to send.";
	option->value = NULL;
	option->flag = OPT_C;
	option->small_print = "Count";
}

static void init_i(t_option *option)
{
	option->name = NULL;
	option->short_name = 'i';
	option->description = "Set the interval between packets in seconds.";
	option->need_value = 1;
	option->check = visint;
	option->arg_help = "Needs an integer to set the interval between packets in seconds.";
	option->value = NULL;
	option->flag = OPT_I;
	option->small_print = "Interval";
}

static void init_s(t_option *option)
{
	option->name = NULL;
	option->short_name = 's';
	option->description = "Set the size of packets.";
	option->need_value = 1;
	option->check = visint;
	option->arg_help = "Needs an integer to set the size of packets.";
	option->value = NULL;
	option->flag = OPT_S;
	option->small_print = "Packetsize";
}

t_option *init_options(int *nb)
{
	*nb = 6;
	if (!*nb)
		return NULL;
	t_option *options = malloc(sizeof(t_option) * *nb);
	if (!options)
		return NULL;
	init_help(&options[0]);
	init_v(&options[1]);
	init_t(&options[2]);
	init_c(&options[3]);
	init_i(&options[4]);
	init_s(&options[5]);

	return options;
}
