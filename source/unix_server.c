#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#define SIZE 80

int main(int argc, char *argv[]){
    int local_socket, new_local_socket, pid, buf;
    socklen_t server_length, client_length;
    ssize_t char_count;
    struct sockaddr_un server_address, client_address;
    char message[SIZE];

    if(argc<2){
        printf("Debe asignarle un nombre al socket como parámetro");
        exit(0);
    }

    local_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    if(local_socket == -1){
        perror("Error en la creación del socket");
        exit(1);
    }

    unlink(argv[1]);

    memset(&)

}   