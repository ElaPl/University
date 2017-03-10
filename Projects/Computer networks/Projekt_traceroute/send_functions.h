#ifndef SEND_FUNCTIONS_H
#define SEND_FUNCTIONS_H
#include "library.h"
int set_time_to_live(int sockfd, int ttl);
u_int16_t compute_icmp_checksum (u_int16_t *buff, int length);
void set_icmp_header(icmphdr* icmphd, int sequence);
int send_packet (int ttl, timeval* start_time, int sockfd, sockaddr_in* recipient, int counter);

#endif
