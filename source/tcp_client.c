#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netdb.h>

#define SIZE 256 //tamaño del buffer

int main(){

    //creo un socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // especifico la dirección del socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002); //puerto probablemente libre
    server_address.sin_addr.s_addr = INADDR_ANY; 

    // connect(socket, estructura con la confuguracion del socket (hay que castearlo), tamaño de la estructura)
    int connection_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));

   // connect devuelve 0 en éxito, -1 en error
    if(connection_status == -1){
        printf("Hubo un error al hacer la conexión \n\n");
    }

    char server_response[SIZE]; // string donde almacenamos la respuesta

    // recibimos datos del servidor y lo almacenamos en el buffer
    recv(network_socket, &server_response, sizeof(server_response), 0);

    printf("El servidor envió esta informacion: %s\n", server_response);

    return 0;
}