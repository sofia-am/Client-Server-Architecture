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

#define MAX_SIZE 65516



