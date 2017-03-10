// Elżbieta Plaszczyk
// Numer indeksu 273005

#include "library.h"

using namespace std;

int set_time_to_live(int sockfd, int ttl) {
    if ((setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int))) < 0) {
        printf("Error: setsockopt, line 42\n");
        return -1;
    }
    return 0;
}
u_int16_t compute_icmp_checksum (u_int16_t *buff, int length) {
	u_int32_t sum;
	const u_int16_t* ptr = buff;
	assert(length % 2 == 0);
	for (sum = 0; length >= 0; length -= 2)
		sum += *ptr++;
	sum = (sum >> 16) + (sum & 0xffff);
	return (u_int16_t)(~(sum + (sum >> 16)));
}
void set_icmp_header(icmphdr* icmphd, int sequence) {
        icmphd->type = ICMP_ECHO;
        icmphd->code = 0;
        icmphd->un.echo.id = (unsigned short)getpid();
        icmphd->un.echo.sequence = sequence;
        icmphd->checksum = 0;
        icmphd->checksum = compute_icmp_checksum((u_int16_t*)icmphd, sizeof(struct icmphdr)) ;
}
int send_packet (int ttl, timeval* start_time, int sockfd, sockaddr_in* recipient, int counter) {
    struct icmphdr* icmphd = (struct icmphdr*) (malloc(sizeof(struct icmphdr)));
    if (set_time_to_live(sockfd, ttl) < 0) return -1;
    set_icmp_header(icmphd, (3*ttl) + counter);
    if(gettimeofday(start_time,NULL)) {
        fprintf(stderr, "Time failed %s\n", strerror(errno));
        return -1;
    }
    ssize_t bwrote = sendto (sockfd, icmphd, sizeof(struct icmphdr), 0, (struct sockaddr*)recipient, sizeof(struct sockaddr_in));
    if (bwrote < 0) {
        fprintf(stderr, "sendto error: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

