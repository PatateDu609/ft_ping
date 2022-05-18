#include "ft_ping.h"
#include "random.h"
#include <unistd.h>
#include <stdio.h>

#include <errno.h>
#include <string.h>
#include <signal.h>

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

static t_icmp_packet *create_packet()
{
	t_icmp_packet *packet;
	char payload[g_data->size];
	size_t total = sizeof(t_icmp_packet) + g_data->size;

	packet = malloc(total);
	ft_memset(packet, 0, sizeof(t_icmp_packet) + g_data->size);

	packet->ip.version = 4;
	packet->ip.ihl = 5;
	packet->ip.tos = 0;
	packet->ip.tot_len = ft_htons(total);
	packet->ip.id = ft_htons(123);
	packet->ip.frag_off = 0;
	packet->ip.ttl = g_data->ttl;
	packet->ip.protocol = IPPROTO_ICMP;
	packet->ip.saddr = INADDR_ANY;
	packet->ip.check = 0;

	packet->hdr.type = ICMP_ECHO;
	packet->hdr.code = 0;
	packet->hdr.un.echo.id = ft_htons(ECHO_ID);
	packet->hdr.un.echo.sequence = ft_htons(g_data->seq);

	generate_payload(payload, g_data->size);
	ft_memcpy(packet->payload, payload, g_data->size);

	packet->hdr.checksum = 0;
	packet->hdr.checksum = ft_cksum((unsigned short *)(&packet->hdr), sizeof(struct icmphdr) + g_data->size);
	return packet;
}

void send_packet(__unused int sig)
{
	int ret;
	size_t total = sizeof(t_icmp_packet) + g_data->size;
	struct sockaddr_in addr;
	struct sockaddr_in *info;

	t_icmp_packet *packet = create_packet(g_data);
	addr.sin_family = AF_INET;
	addr.sin_port = 0;
	info = (struct sockaddr_in *)g_data->infos->ai_addr;
	addr.sin_addr.s_addr = info->sin_addr.s_addr;

	packet->ip.daddr = addr.sin_addr.s_addr;
	packet->ip.check = ft_htons(ft_cksum((unsigned short *)&packet->ip, sizeof(packet->ip)));

	gettimeofday(&g_data->rtt_start, NULL);
	ret = sendto(g_data->sock, packet, total, 0,
				 (const struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0)
		warn("Error sending packet");
	inc_tx();
	free(packet);

	if (g_data->count != -1 && g_data->seq >= g_data->count)
		reset_alarm();
	else if (g_data->seq == 1)
		ft_alarm(g_data->interval);
}

static void print_packet(struct iovec iov, t_icmp_packet *reply)
{
	printf("%zu bytes from ", iov.iov_len);
	if (g_data->fqdn && *g_data->fqdn)
		printf("%s (%s)", g_data->fqdn, g_data->saddr);
	else
		printf("%s", g_data->saddr);

	printf(": icmp_sec=%d ttl=%hhd time=%.1fms\n",
		   ft_ntohs(reply->hdr.un.echo.sequence),
		   reply->ip.ttl,
		   local_rtt(g_data->rtt_start));
}

static void recv_packet()
{
	ssize_t ret = 0;
	struct msghdr hdr;
	struct iovec iov;
	size_t total = sizeof(t_icmp_packet) + g_data->size;
	struct sockaddr_in addr;

	char buf[total];

	ft_memset(&hdr, 0, sizeof(struct msghdr));
	ft_memset(&iov, 0, sizeof(struct iovec));

	ft_memcpy(&addr, g_data->infos->ai_addr, sizeof(struct sockaddr_in));
	hdr.msg_name = &addr;
	hdr.msg_namelen = sizeof(struct sockaddr_in);
	hdr.msg_iov = &iov;
	hdr.msg_iovlen = 1;
	hdr.msg_control = NULL;
	hdr.msg_controllen = 0;
	hdr.msg_flags = 0;

	iov.iov_base = buf;
	iov.iov_len = total;

	ret = recvmsg(g_data->sock, &hdr, 0);
	if (ret < 0)
		warn("Error receiving packet");
	t_icmp_packet *reply = (t_icmp_packet *)buf;
	if (reply->hdr.type == ICMP_ECHOREPLY)
	{
		reply->payload[g_data->size] = 0;
		print_packet(iov, reply);

		if (reply->hdr.un.echo.id == ft_htons(ECHO_ID) &&
			reply->hdr.un.echo.sequence == ft_htons(g_data->seq))
		{
			update_rx();
			g_data->seq++;
		}
	}
	else if (reply->hdr.type != ICMP_ECHO)
	{
		char *err = get_err_mess(reply->hdr.type);
		char mes[256];

		if (reply->hdr.type == ICMP_TIME_EXCEEDED)
			sprintf(mes, "_gateway (%s)", g_data->saddr);
		else
			sprintf(mes, "%s", g_data->saddr);
		printf("From %s: icmp_sec=%hu %s\n", mes, ft_ntohs(reply->hdr.un.echo.sequence), err);

		inc_ex();
	}
}

void __ping()
{
	setup(g_data);

	send_packet(0);

	while (g_data->seq - 1 < g_data->count || g_data->count == -1)
		recv_packet(g_data);

	ft_sighandler(SIGINT);
}
