#include "dependencies.h"
#define SIZE 256
/*
    argv[0]->nombre del programa
    argv[1]->host
    argv[2]->puerto
    argv[3]->tamaño del buffer
*/
int main(int argc, char* argv[]){
    int network_socket;
    struct sockaddr_in6 server_address;
    int connection_status;
    ssize_t char_count;
    //int SIZE = atoi(argv[3]);
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

    while(1){
        printf("Ingrese el mensaje a transmitir: ");
        memset(message, '\0', SIZE); //limpio el buffer
        fgets(message, SIZE-1, stdin);

        char_count = write(network_socket, message, strlen(message));

        if(char_count == -1){
            perror("Hubo un error al enviar el mensaje");
            exit(1);
        }

        memset(message, '\0', SIZE);

        // recibimos datos del servidor y lo almacenamos en el buffer
        char_count = read(network_socket, message, SIZE);

        if(char_count == -1){
            perror("Hubo un error al recibir el mensaje");
            exit(1);
        }
        printf("Respuesta %s\n", message);
    }
    return 0;


}