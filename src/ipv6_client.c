#include "dependencies.h"
/*
    argv[0]->nombre del programa
    argv[1]->puerto
    argv[2]->host
    argv[3]->tamaño del buffer
*/
int main(int argc, char* argv[]){
    int network_socket;
    struct sockaddr_in6 server_address;
    int connection_status;
    ssize_t char_count;
    
    int SIZE = atoi(argv[3]);

    if(SIZE>MAX_SIZE){
        printf("Ingrese un tamaño menor a 1024\n");
        exit(1); 
    }
    char message[SIZE];


    if(argc<2){
        printf("Por favor, ingrese puerto y host");
        exit(0);
    }

    network_socket = socket(AF_INET6, SOCK_STREAM, 0);

    if(network_socket == -1){
        perror("Error en la creación del socket");
        exit(1);
    }

    int puerto = atoi(argv[1]);
    char *address = argv[2];

    server_address.sin6_family = AF_INET6;
    server_address.sin6_port = htons((uint16_t)puerto);
    inet_pton(AF_INET6, address, &server_address.sin6_addr);


    connection_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    if(connection_status == -1){
        perror("Error al hacer la conexion");
        exit(1);
    }
    memset(message, 'a', (size_t)SIZE);
    while(1){

        char_count = write(network_socket, message, strlen(message));

        if(char_count == -1){
            perror("Hubo un error al enviar el mensaje");
            exit(1);
        }
    }
    return 0;


}