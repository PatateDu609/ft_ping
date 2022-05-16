#ifndef DEFINES_H
#define DEFINES_H

#define OPT_V 0x01
#define OPT_H 0x02
#define OPT_T 0x04
#define OPT_C 0x08
#define OPT_I 0x10
#define OPT_S 0x20

#define GET_TIME(rtt) (rtt.tv_sec * 1000000 + rtt.tv_usec)
#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x < y ? y : x)
#define ECHO_ID (uint16_t)42
#define ABS(x) (x < 0 ? -x : x)

#define EWMA_WEIGHT 0.2

#endif
