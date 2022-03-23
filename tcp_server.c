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

    
}