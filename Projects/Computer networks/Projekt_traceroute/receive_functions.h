#ifndef RECEIVE_FUNCTIONS_H
#define RECEIVE_FUNCTIONS_H
#include "library.h"
int receive_packet(int sockfd, timeval* start_time, double* final_time, int ttl, char** ip_str);

#endif
