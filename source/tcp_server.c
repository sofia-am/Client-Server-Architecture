#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <unistd.h>

#define SIZE 256

int main(){
    char server_message[SIZE] = "Te comunicaste con el servidor!";
    
    // creamos el socket de servidor
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // definimos la direccion del servidor
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //bindeamos el socket a nuestro puerto ip especificado
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));


    listen(server_socket, 5); //5: cuantas conexiones puede esperar por este socket en un momento determinado

    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

   //enviamos el mensaje
    send(client_socket, server_message, sizeof(server_message), 0);

    //cerrramos el servidor
    close(server_socket);

    return 0;
}