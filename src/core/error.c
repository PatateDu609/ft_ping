#include "ft_ping.h"

char *get_err_mess(int code)
{
	switch (code)
	{
	case ICMP_DEST_UNREACH:
		return "Destination unreachable";
	case ICMP_SOURCE_QUENCH:
		return "Source quench";
	case ICMP_REDIRECT:
		return "Redirect";
	case ICMP_ECHO:
		return "Echo";
	case ICMP_TIME_EXCEEDED:
		return "Time to live exceeded";
	case ICMP_PARAMETERPROB:
		return "Parameter problem";
	case ICMP_TIMESTAMP:
		return "Timestamp request";
	case ICMP_TIMESTAMPREPLY:
		return "Timestamp reply";
	case ICMP_INFO_REQUEST:
		return "Information request";
	case ICMP_INFO_REPLY:
		return "Information reply";
	case ICMP_ADDRESS:
		return "Address mask request";
	case ICMP_ADDRESSREPLY:
		return "Address mask reply";
	default:
		return "Unknown error";
	}
}
