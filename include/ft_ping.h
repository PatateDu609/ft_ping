#ifndef PING_H
#define PING_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include "ft_getopt.h"

#include "structs.h"

void ping(t_args *args);
void __ping(t_data *data);
void setup(t_data *data);

void throw_error(char *msg);
void warn(char *msg);

uint16_t ft_cksum(uint16_t *addr, int len);

#endif
