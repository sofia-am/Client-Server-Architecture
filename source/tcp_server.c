#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <unistd.h>

#define SIZE 256

int main(/*int argc, char* argv[]*/){
    char message[SIZE]; //= "Te comunicaste con el servidor!";
    int pid;
    
    // creamos el socket de servidor
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1){
        perror("Error en la apertura del socket");
        exit(1);
    }
    
    // definimos la direccion del servidor
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    memset(&server_address, 0, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_address.sin_zero), '\0', 8);

    //bindeamos el socket a nuestro puerto ip especificado
    if(bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) == -1){
        perror("Error al hacer el binding");
        exit(1);
    }

    printf("Proceso %d - Socket disponible %d\n", getpid(), 9002);
    listen(server_socket, 5); //5: cuantas conexiones puede esperar por este socket en un momento determinado

    //socklen_t sv_addr_length = sizeof(server_address);
    socklen_t cl_addr_length = sizeof(client_address);
    //sv_addr_length = sizeof(server_address);   
    ssize_t client_socket;


    while(1){
        
        int new_server_socket = accept(server_socket, (struct sockaddr*)&client_address, &cl_addr_length);
        if(new_server_socket == -1){
            perror("Error al generar un nuevo socket");
            exit(1);
        }

        pid = fork();

        if(pid == 0){
            close(server_socket);

            while(1){
                memset(message, 0, SIZE);

                client_socket = read(new_server_socket, message, SIZE-1);

                if(client_socket == -1){
                    perror("Error en la lectura del socket");
                    exit(1);
                }

                printf("[PID %d]\t", getpid());
                printf("Recibí: %s", message);

                char* respuesta = "Obtuve su mensaje";

                client_socket = write(new_server_socket, respuesta, sizeof(respuesta));

                if(client_socket == -1){
                    perror("Error al escribir en el socket");
                    exit(1);
                }
            }
        }else{
            printf("Servidor: Nuevo cliente, que atiende el proceso hioj %d\n", pid);
            close(new_server_socket);
        }

        return 0;
         // inicializo el buffer en 0
/*
        client_socket = recvfrom(server_socket, message, SIZE-1, 0, (struct sockaddr*)&server_address, &sv_addr_length);
        if(client_socket == -1){
            perror("Error al recibir información");
            exit(1);
        }

        printf("Recibí: %s", message);

        

        client_socket = sendto(server_socket, (void*)&respuesta, sizeof(respuesta), 0, (struct sockaddr*)&server_address, sv_addr_length);
        
        if(client_socket == -1){
            perror("Error al enviar mensaje");
            exit(1);
        }
    }

   //enviamos el mensaje
    send(client_socket, message, sizeof(message), 0);

    //cerrramos el servidor
    close(server_socket);
*/}
}   