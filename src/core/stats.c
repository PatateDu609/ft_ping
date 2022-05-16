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

void inc_ex()
{
	g_data->stat.ex++;
}

static double ft_pow(double x, uint32_t y)
{
	double res = 1;

	while (y--)
		res *= x;
	return res;
}

void update_rx()
{
	g_data->stat.rx++;
	float raw_rtt = timeval_diff(g_data->rtt_start);
	float rtt = raw_rtt / 1000.f;
	g_data->stat.rtt_total += raw_rtt;
	g_data->stat.rtt_m_total += raw_rtt * raw_rtt;

	g_data->stat.rtt_ewma_total += raw_rtt * ft_pow(1 - EWMA_WEIGHT, g_data->stat.rx - 1);
	g_data->stat.rtt_ewma_adjust += ft_pow(1 - EWMA_WEIGHT, g_data->stat.rx - 1);

	g_data->stat.rtt.min = g_data->stat.rtt.min ? MIN(g_data->stat.rtt.min, rtt) : rtt;
	g_data->stat.rtt.max = g_data->stat.rtt.max ? MAX(g_data->stat.rtt.max, rtt) : rtt;
}

void print_stats(uint8_t full)
{
	float loss = (float)(g_data->stat.tx - g_data->stat.rx) / g_data->stat.tx * 100.f;
	double avg = (double)g_data->stat.rtt_total / g_data->stat.tx;
	char errors[64];
	avg /= 1000.f;

	if (g_data->stat.ex)
		snprintf(errors, 64, ", +%d errors", g_data->stat.ex);
	else
		errors[0] = 0;

	if (full)
	{
		long diff = timeval_diff(g_data->tv) / 1000;

		if (diff < 1000)
			diff = 0;

		printf("--- ping statistics ---\n");
		printf("%d packets transmitted, %d received%s, %.3g%% packet loss, time %ldms\n",
			   g_data->stat.tx, g_data->stat.rx, errors, loss, diff);

		if (loss < 100)
		{
			double mdev = g_data->stat.rtt_total / g_data->stat.rx;
			g_data->stat.rtt_m_total /= g_data->stat.rx;
			mdev = ft_sqrt(ABS(g_data->stat.rtt_m_total - mdev * mdev)) / 1000.f;

			printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3lf ms\n",
				   g_data->stat.rtt.min, avg, g_data->stat.rtt.max, mdev);
		}
	}
	else
	{
		double ewma = g_data->stat.rtt_ewma_total / g_data->stat.rtt_ewma_adjust;
		ewma /= 1000.f;

		printf("%d/%d packets, %.3g%% loss, ", g_data->stat.tx, g_data->stat.rx, loss);

		if (loss < 100)
			printf("min/avg/ewma/max = %.3f/%.3f/%.3lf/%.3f ms\n",
				   g_data->stat.rtt.min, avg, ewma, g_data->stat.rtt.max);
	}
}
