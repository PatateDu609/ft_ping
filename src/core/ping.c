#include "ft_ping.h"
#include "random.h"
#include <unistd.h>
#include <stdio.h>

#include <errno.h>
#include <string.h>

static void generate_payload(char *payload, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		payload[i] = (char)pcg64_range(32, 126);
		i++;
	}
}

static t_icmp_packet *create_packet(t_data *data)
{
	t_icmp_packet *packet;
	char payload[data->size];
	size_t total = sizeof(t_icmp_packet) + data->size;

	packet = malloc(total);
	ft_memset(packet, 0, sizeof(t_icmp_packet) + data->size);
	packet->hdr.type = ICMP_ECHO;
	packet->hdr.code = 0;
	packet->hdr.un.echo.id = getpid();
	packet->hdr.un.echo.sequence = data->seq++;

	generate_payload(payload, data->size);
	ft_memcpy(packet->payload, payload, data->size);

	packet->hdr.checksum = 0;
	packet->hdr.checksum = ft_cksum((unsigned short *)packet, total);
	return packet;
}

static void send_packet(t_data *data)
{
	int sock;
	int ret;
	size_t total = sizeof(t_icmp_packet) + data->size;
	struct sockaddr_in addr;
	struct sockaddr_in *info;

	sock = socket(AF_INET, getuid() ? SOCK_DGRAM : SOCK_RAW, IPPROTO_ICMP);
	if (sock < 0)
		throw_error("Error creating socket");

	t_icmp_packet *packet = create_packet(data);
	addr.sin_family = AF_INET;
	addr.sin_port = 0;
	info = (struct sockaddr_in *)data->infos->ai_addr;
	addr.sin_addr.s_addr = info->sin_addr.s_addr;

	ret = sendto(sock, packet, total, 0,
				 (const struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0)
		warn("Error sending packet");
	free(packet);
}

static void recv_packet(__attribute_maybe_unused__ t_data *data)
{
}

void __ping(t_data *data)
{
	setup(data);
	send_packet(data);
	recv_packet(data);
}
