#include "dependencies.h"
/*
    argv[0]->nombre del programa
    argv[1]->host
    argv[2]->puerto
    argv[3]->tamaño del buffer
*/
int main(int argc, char* argv[]){
    int pid1, new_server_socket, server_socket;
    ssize_t char_count = 0;
    struct sockaddr_in server_address, client_address;

    if(argc<2){
        fprintf(stderr, "Ingrese un valor de puerto\n");
        exit(1);
    }

    // creamos el socket de servidor
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(server_socket == -1){
        perror("Error en la apertura del socket");
        exit(1);
    }

    // definimos la direccion del servidor
    memset((char*)&server_address, '0', sizeof(server_address));

    int puerto = atoi(argv[1]); //el nro de puerto es pasado como argumento
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons((uint16_t)puerto);
    server_address.sin_addr.s_addr = INADDR_ANY;
    //memset(&(server_address.sin_zero), '\0', 8);

    //bindeamos el socket a nuestro puerto ip especificado
    if(bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) == -1){
        perror("Error al hacer el binding");
        exit(1);
    }

    printf("ᴍᴏꜱʜɪ ᴍᴏꜱʜɪ!\n[IPV4] Servidor: PID %d - Socket disponible en puerto %d\n", getpid(), ntohs(server_address.sin_port));
    listen(server_socket, 5); //5: cuantas conexiones puede esperar por este socket en un momento determinado

    socklen_t cl_addr_length = sizeof(client_address);

    signal(SIGCHLD, SIG_IGN);

    while(1){
        
        new_server_socket = accept(server_socket, (struct sockaddr*)&client_address, &cl_addr_length);
        if(new_server_socket == -1){
            perror("Error al generar un nuevo socket");
            exit(1);
        }

        pid1 = fork();

        if(pid1 == 0){
            close(server_socket);
            //fprintf(stdout, "[PID %d] Atendiendo nuevo cliente", getpid());
            while(1){
                char message[MAX_SIZE]; 
                memset(message, 0, (size_t)MAX_SIZE);

                char_count = read(new_server_socket, message, (size_t)MAX_SIZE-1);

                if(char_count == -1){
                    perror("Error en la lectura del socket");
                    exit(1);
                }
            }
        }else{
            printf("[IPV4] PID %d - Atendiendo un nuevo cliente\n", pid1);

            close(new_server_socket);
        }
    }
    return 0;
}   