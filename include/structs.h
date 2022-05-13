#ifndef STRUCTS_H
#define STRUCTS_H

#include <stddef.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#include "ft_getopt.h"

typedef struct s_data
{
	t_args *args;
	struct addrinfo *infos;
	size_t size;
	uint16_t seq;
	int32_t sock;
} t_data;

typedef struct s_icmp_packet
{
	struct icmphdr hdr;
	char payload[];
} t_icmp_packet; 

typedef struct s_icmp_packet_reply
{
	struct iphdr iphdr;
	struct icmphdr hdr;
	char payload[];
} t_icmp_packet_reply;

#endif
