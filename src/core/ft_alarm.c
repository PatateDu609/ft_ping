#include "ft_ping.h"
#include <sys/time.h>

void ft_alarm(int ms)
{
	struct itimerval it;
	struct timeval tv;

	tv.tv_sec = ms / 1000;
	tv.tv_usec = (ms % 1000) * 1000;

	it.it_interval = tv;
	it.it_value = tv;
	setitimer(ITIMER_REAL, &it, NULL);
}

void reset_alarm()
{
	struct itimerval it;

	it.it_interval.tv_sec = 0;
	it.it_interval.tv_usec = 0;
	it.it_value.tv_sec = 0;
	it.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &it, NULL);
}
