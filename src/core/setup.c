#include "ft_ping.h"
#include <stdio.h>

static void print_init(char *name, char *ip, size_t size)
{
	size_t hdr = sizeof(struct icmphdr) + sizeof(struct iphdr);
	printf("PING %s (%s) %zu(%zu) bytes of data.\n", name, ip, size, size + hdr);
}

void setup(t_data *data)
{
	char *name;
	char ip[INET_ADDRSTRLEN];
	struct sockaddr_in *addr;

	addr = (struct sockaddr_in *)data->infos->ai_addr;

	inet_ntop(AF_INET, &addr->sin_addr, ip, INET_ADDRSTRLEN);
	name = data->infos->ai_canonname ? data->infos->ai_canonname : "";

	print_init(name, ip, data->size);
}
