#include "utils.h"
#include <inttypes.h>

static uint8_t check_endian()
{
	int x = 0x01234567;

	return *(uint8_t *)&x == 0x67;
}

uint16_t ft_htons(uint16_t hostshort)
{
	return check_endian() ? (hostshort & 0xFF00) >> 8 | (hostshort & 0x00FF) << 8 : hostshort;
}

uint32_t ft_htonl(uint32_t hostlong)
{
	if (check_endian())
		return hostlong >> 24 |
			   (hostlong & 0xFF0000) >> 8 |
			   (hostlong & 0x00FF00) << 8 |
			   hostlong << 24;
	return hostlong;
}

uint16_t ft_ntohs(uint16_t netshort)
{
	return ft_htons(netshort);
}

uint32_t ft_ntohl(uint32_t netlong)
{
	return ft_htonl(netlong);
}
