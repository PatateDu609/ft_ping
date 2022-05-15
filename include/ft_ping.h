#ifndef PING_H
#define PING_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include "ft_getopt.h"

#include "structs.h"

#define GET_TIME(rtt) (rtt.tv_sec * 1000000 + rtt.tv_usec)
#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x < y ? y : x)
#define ECHO_ID (uint16_t)42
#define ABS(x) (x < 0 ? -x : x)

#define EWMA_WEIGHT 0.2

void ping(t_args *args);
void __ping();
void send_packet(__attribute_maybe_unused__ int sig);
void setup();

void throw_error(char *msg);
void warn(char *msg);

uint16_t ft_cksum(uint16_t *addr, int len);

void ft_sighandler(int sig);

float local_rtt(struct timeval rtt_start);
void inc_tx();
void update_rx();
void print_stats(uint8_t full);

uint16_t ft_htons(uint16_t hostshort);
uint32_t ft_htonl(uint32_t hostlong);
uint16_t ft_ntohs(uint16_t netshort);
uint32_t ft_ntohl(uint32_t netlong);

double ft_sqrt(double x);

#endif
