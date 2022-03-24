#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <errno.h>

#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

typedef struct Data
{
    int ipv4_size;
    int ipv6_size;
    int unix_size;
}data;

data socket_data;
