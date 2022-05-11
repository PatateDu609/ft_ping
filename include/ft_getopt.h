#ifndef FT_GETOPT_H
#define FT_GETOPT_H

#include <stddef.h>
#include <stdlib.h>
#include <inttypes.h>

#include "utils.h"

typedef struct s_option
{
	char short_name;
	char *name;
	char *description;
	uint8_t *value;
	uint8_t flag;
} t_option;

typedef struct s_args
{
	char **args;
	char flags;
	int nb_opt;
	t_option *options;
} t_args;

int8_t get_option(t_option *options, int nb_opt, char *arg);
t_option *init_options(int *nb);
void print_flags(uint8_t flags, t_option *options);
t_args *parse_args(int ac, char **av);
void print_help(t_args *args);

#endif
