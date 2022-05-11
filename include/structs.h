#ifndef STRUCTS_H
#define STRUCTS_H

#include <stddef.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/ip_icmp.h>

#include "ft_getopt.h"

typedef struct s_data
{
	t_args *args;
	struct addrinfo *infos;
} t_data;

#endif