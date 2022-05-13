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
	packet->hdr.un.echo.sequence = data->seq;

	generate_payload(payload, data->size);
	ft_memcpy(packet->payload, payload, data->size);

	packet->hdr.checksum = 0;
	packet->hdr.checksum = ft_cksum((unsigned short *)packet, total);
	return packet;
}

static void send_packet(t_data *data)
{
	int ret;
	size_t total = sizeof(t_icmp_packet) + data->size;
	struct sockaddr_in addr;
	struct sockaddr_in *info;

	t_icmp_packet *packet = create_packet(data);
	addr.sin_family = AF_INET;
	addr.sin_port = 0;
	info = (struct sockaddr_in *)data->infos->ai_addr;
	addr.sin_addr.s_addr = info->sin_addr.s_addr;

	ret = sendto(data->sock, packet, total, 0,
				 (const struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0)
		warn("Error sending packet");
	free(packet);
}

static char *get_name(struct msghdr msg)
{
	t_icmp_packet *reply = (t_icmp_packet *)msg.msg_iov[0].iov_base;
	char *name = NULL;

	if (reply->hdr.type == ICMP_ECHOREPLY)
	{
		// struct in_addr addr;
		// addr.s_addr = reply->iphdr.saddr;
		// name = inet_ntoa(addr);
	}
	return name;
}

static void recv_packet(t_data *data)
{
	ssize_t ret = 0;
	struct msghdr hdr;
	struct iovec iov;
	size_t total = sizeof(t_icmp_packet) + data->size;
	char buf[total];

	ft_memset(&hdr, 0, sizeof(struct msghdr));
	ft_memset(&iov, 0, sizeof(struct iovec));
	hdr.msg_name = NULL;
	hdr.msg_namelen = 0;
	hdr.msg_iov = &iov;
	hdr.msg_iovlen = 1;
	hdr.msg_control = NULL;
	hdr.msg_controllen = 0;
	hdr.msg_flags = 0;

	iov.iov_base = buf;
	iov.iov_len = total;
	
	ret = recvmsg(data->sock, &hdr, 0); 
	if (ret < 0)
		warn("Error receiving packet");
	else
	{
		t_icmp_packet *reply = (t_icmp_packet *)buf;
		reply->payload[data->size] = 0;
		printf("%ld bytes from %s\n", ret, get_name(hdr));
		if (reply->hdr.type == ICMP_ECHOREPLY)
		{
			if (reply->hdr.un.echo.id == getpid())
			{
				if (reply->hdr.un.echo.sequence == data->seq - 1)
					data->seq++;
			}
		}
	}
}

void __ping(t_data *data)
{
	setup(data);
	send_packet(data);
	recv_packet(data);
}
