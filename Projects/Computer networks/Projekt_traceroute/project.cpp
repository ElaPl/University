// Elżbieta Plaszczyk
// Numer indeksu 273005
#include "library.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (check_args(argc, argv) == 0) return EXIT_FAILURE;
    int sockfd = createRaw();
    if (sockfd < 0) return EXIT_FAILURE;

    struct timeval start_time;
    double final_time = 0.0;
    int ttl = 1;
    char** ip_str ;
    ip_str = (char**) malloc(3*sizeof(char*));
    for (int i = 0; i < 3; i++) ip_str[i] = (char*) "";
    struct sockaddr_in recipient = make_sockaddr_in(argv[1]);
    while(ttl <= 30) {
        reset_time(&start_time, 0);


        for (int i = 0; i < 3; i++) {
            if ((send_packet(ttl, &start_time, sockfd, &recipient, i)) != 0) {
                return EXIT_FAILURE;
            }
        }

        int counter = receive_packet(sockfd, &start_time, &final_time, ttl, ip_str);

        if (counter == -1) return EXIT_FAILURE;
        print_result(ip_str, final_time/3.0, ttl, counter);
        if (check_result(argv[1], ip_str)) return 0;
        ttl++;
        final_time = 0.0;
    }
    return 0;
}
