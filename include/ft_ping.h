#ifndef PING_H
#define PING_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include "ft_getopt.h"

#include "structs.h"
#include "defines.h"

void ping(t_args *args);
void __ping();
void send_packet(__unused int sig);
void setup();

char *get_err_mess(int code);

void throw_error(char *msg);
void warn(char *msg);

uint16_t ft_cksum(uint16_t *addr, int len);

void ft_sighandler(int sig);

float local_rtt(struct timeval rtt_start);
void inc_tx();
void inc_ex();
void update_rx();
void print_stats(uint8_t full);

uint16_t ft_htons(uint16_t hostshort);
uint32_t ft_htonl(uint32_t hostlong);
uint16_t ft_ntohs(uint16_t netshort);
uint32_t ft_ntohl(uint32_t netlong);

double ft_sqrt(double x);

void ft_alarm(int ms);
void reset_alarm();

#endif
