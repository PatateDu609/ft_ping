#include "ft_ping.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void print_init(char *name, size_t size)
{
	size_t hdr = sizeof(struct icmphdr) + sizeof(struct iphdr);
	printf("PING %s (%s) %zu(%zu) bytes of data.\n", name, g_data->saddr, size, size + hdr);
}

void setup()
{
	char *name;
	struct sockaddr_in *addr;
	int on = 1;

	addr = (struct sockaddr_in *)g_data->infos->ai_addr;

	inet_ntop(AF_INET, &addr->sin_addr, g_data->saddr, INET_ADDRSTRLEN);
	name = g_data->infos->ai_canonname ? g_data->infos->ai_canonname : "";

	g_data->sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (g_data->sock < 0)
		throw_error("Error creating socket");
	if (setsockopt(g_data->sock, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0)
		throw_error("Error setting socket options");

	if (signal(SIGINT, ft_sighandler) == SIG_ERR ||
		signal(SIGQUIT, ft_sighandler) == SIG_ERR ||
		signal(SIGALRM, send_packet) == SIG_ERR)
		throw_error("Error on signal setup");

	ft_memset(&g_data->stat, 0, sizeof(g_data->stat));

	ft_memset(g_data->fqdn, 0, sizeof(g_data->fqdn));

	if (!(g_data->args->flags & OPT_N))
		getnameinfo(g_data->infos->ai_addr, g_data->infos->ai_addrlen,
					g_data->fqdn, sizeof(g_data->fqdn), NULL, 0, NI_NAMEREQD);

	gettimeofday(&g_data->tv, NULL);
	print_init(name, g_data->size);
}
