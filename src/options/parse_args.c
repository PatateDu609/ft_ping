#include "ft_getopt.h"

static int get_size(int ac, char **av, int *s, uint8_t opt)
{
	int size = 0;

	for (int i = 1; i < ac; i++)
	{
		if (!*s && av[i][0] == '-' && av[i][1] == '-' && av[i][2] == 0)
		{
			*s = i + 1;
			continue;
		}
		else if (!*s && av[i][0] == '-')
		{
			if (opt)
				continue;
			*s = -1;
			return -1;
		}
		else if (!*s)
			*s = i;
		if (!*s)
			continue;
		size++;
	}
	return size;
}

static uint8_t extract_args(int ac, char **av, t_args *args)
{
	int s = 0;
	int size = get_size(ac, av, &s, args->nb_opt > 0);

	if (s == -1)
	{
		print_help(args);
		return 0;
	}
	args->args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!args->args)
		return 2;
	args->args[size] = NULL;

	if (size == 0)
		return 1;
	for (int i = s; i < ac; i++)
		args->args[i - s] = av[i];
	return (1);
}

static uint8_t extract_flags(int ac, char **av, t_args *args)
{
	if (!args->options)
		return 1;
	for (int i = 1; i < ac; i++)
	{
		int8_t opt = get_option(args->options, args->nb_opt, av[i]);
		if (opt == -1)
		{
			print_help(args);
			return 0;
		}
		args->flags |= opt;
	}
	return 1;
}

t_args *parse_args(int ac, char **av)
{
	t_args *args;

	if (!(args = (t_args *)malloc(sizeof(t_args))))
		return NULL;
	args->options = init_options(&args->nb_opt);
	if (!extract_flags(ac, av, args))
	{
		free(args->options);
		free(args);
		return (void *)-1;
	}
	uint8_t ret = extract_args(ac, av, args);
	if (!ret)
	{
		free(args->options);
		free(args->args);
		free(args);
		return (void *)-1;
	}
	else if (ret == 2)
	{
		free(args->options);
		free(args);
		return NULL;
	}
	return args;
}
