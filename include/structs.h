#ifndef STRUCTS_H
#define STRUCTS_H

#include <stddef.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#include <sys/time.h>

#include "ft_getopt.h"

typedef struct s_stat
{
	uint32_t tx;
	uint32_t rx;
	uint32_t ex;

	float rtt_total;
	float rtt_m_total;

	double rtt_ewma_total;
	double rtt_ewma_adjust;

	struct
	{
		float min;
		float max;
		float avg;
		float mdev;
	} rtt;
} t_stat;

typedef struct s_data
{
	t_args *args;
	struct addrinfo *infos;
	uint16_t seq;
	int32_t sock;
	struct timeval tv;

	size_t size;
	uint8_t ttl;
	ssize_t count;
	uint16_t interval;
	char fqdn[NI_MAXHOST];
	char saddr[INET_ADDRSTRLEN];

	struct timeval rtt_start;
	t_stat stat;
} t_data;

typedef struct s_icmp_packet
{
	struct iphdr ip;
	struct icmphdr hdr;
	char payload[];
} t_icmp_packet;

extern t_data *g_data;

#endif
