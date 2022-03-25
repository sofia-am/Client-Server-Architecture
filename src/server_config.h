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

#include <sys/ipc.h>
#include <sys/shm.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_SIZE 65516
#define MBIT 1000000

typedef struct Data
{
    long int ipv4_bytes;
    long int ipv6_bytes;
    long int unix_bytes;
}data;

int ipv4_server(char argv[], long int *ipv4_bytes);
int ipv6_server(char argv[], long int *ipv6_bytes);
int unix_server(char argv[], long int *unix_bytes);
