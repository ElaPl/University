// Elżbieta Plaszczyk
// Numer indeksu 273005

#include "library.h"

bool check_args(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Need destination IP adress\n");
        return 0;
    }
    else {
        int adr_len = strlen(argv[1]);
        int sign, counter = 0, number = 0;
        for (int i = 0 ; i < adr_len; i++) {
            sign = (int)argv[1][i];
            if (sign >= 48 && sign <= 57) {
                counter++;
            }
            if (sign == 46) {
                if (counter == 0) {
                    fprintf(stderr, "Wrong address IP\n");
                    return false;
                }
                number++;
                counter = 0;
            }
            if (counter == 5) {
                fprintf(stderr, "Wrong address IP\n");
                return false;
            }
            if (sign == 47 || sign < 46 || sign > 57 ) {
                fprintf(stderr, "Wrong address IP\n");
                return false;
            }
        }
        if (counter > 4 || counter == 0) {
            fprintf(stderr, "Wrong address IP\n");
            return false;
        }
        if (number != 3) {
            fprintf(stderr, "Wrong address IP\n");
            return false;
        }
        return true;
    }
}
int createRaw() {
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno));
		return sockfd;
	} else {
		return sockfd;
	}
}
sockaddr_in make_sockaddr_in(char* address) {
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, address , &(addr.sin_addr));
    return addr;
}
void reset_time(timeval* time, int sec) {
    time->tv_sec  = sec;
    time->tv_usec  = 0;
}
bool check_result(char* ip_dst, char** ip_str) {
    for (int i = 0; i < 3; i++) {
        if (strcmp(ip_dst, ip_str[i]) != 0) {
            return false;
        }
    }
    return true;
}
void print_result (char** ip_str, double time, int ttl, int counter) {
    if (counter == 0) printf("%d. *\n", ttl);
    else {
        printf ("%d. %s ", ttl, ip_str[0]);
        if (strcmp(ip_str[0], ip_str[1]) != 0) printf("%s ", ip_str[1]);
        if ((strcmp(ip_str[0], ip_str[2]) != 0) && (strcmp(ip_str[1], ip_str[2]) != 0)) printf("%s ", ip_str[2]);
        if (counter != 3) printf ("???\n");
        if (counter == 3) printf("%dms\n", (int)time);
    }
}
double compute_time(timeval* end_time, timeval *start_time) {
    double part_time = (end_time->tv_usec - start_time->tv_usec)/1000.0;
    if (part_time < 0) {
        part_time += 1000.0;
    }
    return part_time;
 }

