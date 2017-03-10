// Elżbieta Plaszczyk
// Numer indeksu 273005

#include "library.h"

using namespace std;

int receive_packet(int sockfd, timeval* start_time, double* final_time, int ttl, char** ip_str) {
    timeval end_time, timeout;
    reset_time(&end_time, 0);

    struct sockaddr_in 	sender;
    socklen_t 			sender_len = sizeof(sender);
    u_int8_t 			buffer[IP_MAXPACKET+1];

    int counter = 0;
    fd_set readfds;
    FD_ZERO (&readfds);
    FD_SET (sockfd, &readfds);
    reset_time(&timeout, 1);

    while (counter < 3) {
        int rfds = select(sockfd + 1, &readfds, NULL, NULL, &timeout);
            if (rfds == -1) {
                printf("Can not read!!!");
                return -1;
            }
            if (rfds == 0 ) {
                return counter;
            }
            if (rfds == 1) {
                ssize_t packet_len = recvfrom (sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
                if (packet_len < 0) {
                    fprintf(stderr, "recvfrom error: %s\n", strerror(errno));
                    return -1;
                }
                char sender_ip_str[20];
                inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));
                struct icmphdr* recv_icmp = (struct icmphdr*) (buffer + packet_len - sizeof(struct icmphdr));

                if ((recv_icmp -> un.echo.sequence / 3) == ttl) {
                    if(gettimeofday(&end_time,NULL)) {
                        printf("time failed\n");
                        return -1;
                    }
                    *final_time += compute_time(&end_time, start_time);
                    int r = (recv_icmp -> un.echo.sequence % 3);
                    ip_str[r] = sender_ip_str;
                    counter++;
                    reset_time(&end_time, 0);
                }
            }
        }
    return counter;
}



