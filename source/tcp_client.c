#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netdb.h>

#define SIZE 256 //tamaño del buffer

int main(int argc, char *argv[]){

    if(argc<3){
        fprintf(stderr, "Ingrese un host y un puerto\n");
        exit(0);
    }

    //creo un socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    int puerto = atoi(argv[2]);
    struct hostent *server = gethostbyname(argv[1]); //me pasan como parámetro el servidor

    // especifico la dirección del socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons((uint16_t)puerto); //puerto probablemente libre
    //server_address.sin_addr.s_addr = server->h_addr; 
    bcopy((char*)server->h_addr, (char*)&server_address.sin_addr.s_addr, (size_t)server->h_length); //copia n bits de source a destino (src, dest, n)

    // connect(socket, estructura con la confuguracion del socket (hay que castearlo), tamaño de la estructura)
    int connection_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));

   // connect devuelve 0 en éxito, -1 en error
    if(connection_status == -1){
        perror("Hubo un error al hacer la conexión \n\n");
        exit(1);
    }

    while(1){
        printf("Ingrese el mensaje a transmitir: ");
        
        char message[SIZE]; // string donde almacenamos la respuesta
        memset(message, '\0', SIZE); //limpio el buffer
        fgets(message, SIZE-1, stdin);

        ssize_t char_count; //nos dice cuantos caracteres fueron escritos/leídos con éxito

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