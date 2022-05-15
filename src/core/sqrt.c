#include "ft_ping.h"
#include <math.h>

double ft_sqrt(double x)
{
	if (x < 0)
		return (-1);

	double pr, vmin, vmax, m;

	pr = __DBL_EPSILON__ * 10;
	vmin = 0;
	vmax = x / 2;

	do
	{
		m = (vmin + vmax) / 2;
		if (m * m > x)
			vmax = m;
		else
			vmin = m;
	} while (ABS(m * m - x) > pr);
	return (m);
}
