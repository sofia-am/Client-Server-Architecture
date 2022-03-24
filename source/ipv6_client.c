#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define SIZE 256

int main(int argc, char* argv[]){
    int network_socket;
    struct sockaddr_in6 server_address;
    int connection_status;
    char* message[SIZE];

    network_socket = socket(AF_INET6, SOCK_STREAM, 0);

    if(network_socket == -1){
        perror("Error en la creación del socket");
        exit(1);
    }

    struct hostent *server = gethostbyname(argv[1]);

    server_address.sin6_family = AF_INET6;
    server_address.sin6_port = htons(7002);
    inet_pton(AF_INET6, argv[1], &server_address.sin6_addr);

    connection_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    if(connection_status == -1){
        perror("Error al hacer la conexion");
        exit(1);
    }


}