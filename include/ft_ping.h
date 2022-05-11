#ifndef PING_H
#define PING_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "ft_getopt.h"

#include "structs.h"

void ping(t_args *args);

void throw_error(char *msg);

#endif