#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <errno.h>

#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAX_SIZE 1024

int ipv4_server(char argv[]);
int ipv6_server(char argv[]);
int unix_server(char argv[]);
