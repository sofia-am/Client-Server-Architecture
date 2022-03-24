#include "dependencies.h"

int main(int argc, char* argv[]){
    int listen_socket, new_socket;
    struct sockaddr_in6 server_address, client_address;
    socklen_t client_address_length;
    //char message[INET6_ADDRSTRLEN];
    int pid;
    ssize_t char_count;

    if(argc<2){
        fprintf(stderr, "Ingrese un valor de puerto\n");
        exit(1);
    }

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

    if(client_address_length == 0){
        perror("Error en la dirección");
        exit(1);
    }

    while(1){
        new_socket = accept(listen_socket, (struct sockaddr*)&client_address, &client_address_length);
        if(new_socket == -1){
            perror("Error al generar un nuevo socket");
            exit(1);
        }

        pid = fork();

        if(pid == 0){
            close(listen_socket);

            while(1){
                int SIZE = socket_data.ipv6_size;
                char message[SIZE];
                memset(message, 0, (size_t)SIZE);

                char_count = read(new_socket, message, (size_t)SIZE-1);

                if(char_count == -1){
                    perror("Error en la lectura del socket");
                    exit(1);
                }

                printf("\n[PID %d]\t", getpid());
                printf("Recibí %s", message);

                char_count = write(new_socket, "Recibí el mensaje", 18);
                if(char_count == -1){
                    perror("Error en la escritura del socket");
                    exit(1);
                }
            }
        }else{
                printf("Servidor: Nuevo cliente, atendido por el proceso %d\n", pid);
                close(new_socket);
        }
    }
    return 0;
}

    
