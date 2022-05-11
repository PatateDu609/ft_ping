#include "ft_getopt.h"

static int8_t manage_short_opt(t_option *opts, int nb_opts, char *arg)
{
	int8_t flags;

	for (int i = 1; arg[i]; i++)
	{
		uint8_t valid = 0;

		for (int j = 0; j < nb_opts; j++)
		{
			if (opts[j].short_name == arg[i])
			{
				flags |= opts[j].flag;
				valid = 1;
				break;
			}
		}
		if (!valid)
			return -1;
	}
	return flags;
}

static int8_t manage_long_opt(t_option *opts, int nb_opts, char *arg)
{

	for (int i = 0; i < nb_opts; i++)
		if (ft_strcmp(opts[i].name, arg + 2) == 0)
			return opts[i].flag;
	return -1;
}

int8_t get_option(t_option *options, int nb_opts, char *arg)
{
	if (arg[0] == '-' && arg[1] == '-')
		return manage_long_opt(options, nb_opts, arg);
	else if (arg[0] == '-')
		return manage_short_opt(options, nb_opts, arg);
	return 0;
}
