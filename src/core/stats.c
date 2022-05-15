#include "ft_ping.h"
#include <stdio.h>

static suseconds_t timeval_diff(struct timeval rtt_start)
{
	suseconds_t start = GET_TIME(rtt_start);
	suseconds_t end;
	struct timeval rtt_end;

	gettimeofday(&rtt_end, NULL);
	end = GET_TIME(rtt_end);
	return end - start;
}

float local_rtt(struct timeval rtt_start)
{
	return timeval_diff(rtt_start) / 1000.f;
}

void inc_tx()
{
	g_data->stat.tx++;
}

void update_rx()
{
	g_data->stat.rx++;
	suseconds_t rtt = timeval_diff(g_data->rtt_start);
	g_data->stat.rtt_total += rtt;

	g_data->stat.rtt.min = g_data->stat.rtt.min ? MIN(g_data->stat.rtt.min, rtt) : rtt;
	g_data->stat.rtt.max = g_data->stat.rtt.max ? MAX(g_data->stat.rtt.max, rtt) : rtt;
}

void print_stats(uint8_t full)
{
	if (full)
	{
		long diff = timeval_diff(g_data->tv) / 1000;
		printf("--- ping statistics ---\n");
		printf("%d packets transmitted, %d received, %d%% packet loss, time %ldms\n",
			   g_data->stat.tx, g_data->stat.rx,
			   (g_data->stat.tx - g_data->stat.rx) / g_data->stat.tx * 100,
			   diff);
	}
}
