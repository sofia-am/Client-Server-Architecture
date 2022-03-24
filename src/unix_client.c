#include "dependencies.h"


int main(int argc, char*argv[]){
    int SIZE = atoi(argv[2]);
    int local_socket;
    ssize_t char_count, connection_status;
    socklen_t server_length;
    struct sockaddr_un server_address;

    if(SIZE>MAX_SIZE){
        printf("Ingrese un tamaño menor a 1024");
        exit(1);
    }
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

    connection_status = connect(local_socket, (struct sockaddr*)&server_address, server_length);
    
    if(connection_status == -1){
        perror("Error en la conexión");
        exit(1);
    }

    while(1){
        memset(message, 'a', (size_t)SIZE);
        //printf("Ingrese el mensaje a enviar: ");
        //fgets(message, SIZE-1, stdin);

        char_count = write(local_socket, message, strlen(message));

        if(char_count < 0){
            perror("Error en la escritura del socket");
            exit(1);
        }

        memset(message, '\0', (size_t)SIZE);
        char_count = read(local_socket, message, (size_t)SIZE);

        if(char_count < 0){
            perror("Error en la lectura del socket");
            exit(1);
        }

        //printf("Respuesta %s\n", message);
    }
    return 0;
}