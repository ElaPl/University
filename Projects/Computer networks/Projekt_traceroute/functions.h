
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "library.h"


bool check_args(int argc, char *argv[]);
int createRaw();
double compute_time(timeval* start_time, timeval* end_time);
sockaddr_in make_sockaddr_in(char* address);
void reset_time(timeval* time, int sec);
bool check_result(char* ip_dst, char** ip_str);
void print_result (char** ip_str, double time, int ttl, int counter);


#endif


