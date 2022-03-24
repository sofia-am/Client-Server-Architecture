#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#define SIZE 80

int main(int argc, char*argv[]){

    int local_socket;
    ssize_t char_count,c_flag;
    socklen_t server_length;
    struct sockaddr_un server_address;
    char message[SIZE];
    //int terminar = 0;

    if(argc<2){
        fprintf(stderr, "Debe ingresar un archivo como parámetro\n");
        exit(0);
    }

    memset((char*)&server_address, '\0', sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path,argv[1]);
    server_length = (socklen_t)(strlen(server_address.sun_path)+(size_t)sizeof(server_address.sun_family));

    local_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    
    if(local_socket == -1){
        perror("Error en la creación del socket");
        exit(1);
    }

    c_flag = connect(local_socket, (struct sockaddr*)&server_address, server_length);
    
    if(c_flag == -1){
        perror("Error en la conexión");
        exit(1);
    }

    while(1){
        memset(message, '\0', SIZE);
        printf("Ingrese el mensaje a enviar: ");
        fgets(message, SIZE-1, stdin);

        char_count = write(local_socket, message, strlen(message));

        if(char_count < 0){
            perror("Error en la escritura del socket");
            exit(1);
        }

        memset(message, '\0', SIZE);
        char_count = read(local_socket, message, SIZE);
        printf("Respuesta %s\n", message);
    }
    return 0;
}