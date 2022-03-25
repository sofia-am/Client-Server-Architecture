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

typedef struct Data
{
    int ipv4_size;
    int ipv6_size;
    int unix_size;
}data;

data socket_data;

int ipv4_client(char argv[]);
int ipv6_client(char argv[]);
int unix_client(char argv[]);


