#include "dependencies.h"

int main(int argc, char* argv[]){
    int listen_socket, client_socket, new_socket;
    struct sockaddr_in6 server_address, client_address;
    socklen_t client_address_length;
    char message[INET6_ADDRSTRLEN];
    int pid;
    char ch;

    listen_socket = socket(AF_INET6, SOCK_STREAM, 0);
    if(listen_socket == -1){
        perror("Error al crear el socket");
        exit(1);
    }

    server_address.sin6_family = AF_INET6;
    inet_pton(AF_INET6, argv[1], &server_address.sin6_addr);
    server_address.sin6_port = htons(7002);

    listen(listen_socket, 5);

    client_address_length = sizeof(client_address);

    while(1){
        new_socket = accept(listen_socket, (struct sockaddr*)&client_address, &client_address_length);
        if(new_socket == -1){
            perror("Error al generar un nuevo socket");
            exit(1);
        }

        pid = fork();
    }

    
}