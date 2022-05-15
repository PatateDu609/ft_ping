#include "ft_ping.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void print_init(char *name, char *ip, size_t size)
{
	size_t hdr = sizeof(struct icmphdr) + sizeof(struct iphdr);
	printf("PING %s (%s) %zu(%zu) bytes of data.\n", name, ip, size, size + hdr);
}

void setup()
{
	char *name;
	char ip[INET_ADDRSTRLEN];
	struct sockaddr_in *addr;

	addr = (struct sockaddr_in *)g_data->infos->ai_addr;

	inet_ntop(AF_INET, &addr->sin_addr, ip, INET_ADDRSTRLEN);
	name = g_data->infos->ai_canonname ? g_data->infos->ai_canonname : "";

	g_data->sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP);
	if (g_data->sock < 0)
		throw_error("Error creating socket");

	if (signal(SIGINT, ft_sighandler) == SIG_ERR ||
		signal(SIGQUIT, ft_sighandler) == SIG_ERR ||
		signal(SIGALRM, send_packet) == SIG_ERR)
		throw_error("Error on signal setup");

	gettimeofday(&g_data->tv, NULL);
	print_init(name, ip, g_data->size);
}
