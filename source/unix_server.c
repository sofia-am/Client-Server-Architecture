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
    ssize_t char_count, b_flag;
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

    memset((void*)&server_address, 0, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, argv[1]); //almaceno el nombre del socket que pasé como parametro
    server_length = (socklen_t)(strlen(server_address.sun_path)+sizeof(server_address.sun_family));

    b_flag = bind(local_socket, (struct sockaddr*)&server_address, server_length);

    if(b_flag == -1){
        perror("Error al hacer el bind");
        exit(1);
    }

}   