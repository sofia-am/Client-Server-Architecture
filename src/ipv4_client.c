#include "dependencies.h"
/*
    argv[0]->nombre del programa
    argv[1]->host
    argv[2]->puerto
    argv[3]->tamaño del buffer
*/

int main(int argc, char *argv[]){
    int SIZE = atoi(argv[3]);

    if(SIZE>MAX_SIZE){
        printf("Ingrese un tamaño menor a 1024");
        exit(1);
    }

    char message[SIZE]; // string donde almacenamos la respuesta
    //socket_data.ipv4_size = SIZE; //seteo en la estructura compartida entre el cliente y el servidor el tamaño de buffer a utilizar

    ssize_t char_count; //nos dice cuantos caracteres fueron escritos/leídos con éxito
    int network_socket;

    if(argc<3){
        fprintf(stderr, "Ingrese un host y un puerto\n");
        exit(0);
    }
    //creo un socket
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    int puerto = atoi(argv[2]);
    struct hostent *server = gethostbyname(argv[1]); //me pasan como parámetro el servidor

    // especifico la dirección del socket
    struct sockaddr_in server_address;
    memset((char*)&server_address, '0', sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons((uint16_t)puerto); //puerto probablemente libre
    //server_address.sin_addr.s_addr = server->h_addr; 
    bcopy((char*)server->h_addr, (char*)&server_address.sin_addr.s_addr, (size_t)server->h_length); //copia n bits de source a destino (src, dest, n)

    // connect(socket, estructura con la confuguracion del socket (hay que castearlo), tamaño de la estructura)
    int connection_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));

   // connect devuelve 0 en éxito, -1 en error
    if(connection_status == -1){
        perror("Hubo un error al hacer la conexión");
        exit(1);
    }  

    //printf("Ingrese el mensaje a transmitir: ");
   // memset(message, '\0', (size_t)SIZE); //limpio el buffer
    //fgets(message, SIZE-1, stdin);


    while(1){
        memset(message, 'a', (size_t)SIZE);
        
        char_count = write(network_socket, message, strlen(message));

        if(char_count == -1){
            perror("Hubo un error al enviar el mensaje");
            exit(1);
        }

        memset(message, '\0', (size_t)SIZE);

        // recibimos datos del servidor y lo almacenamos en el buffer
        char_count = read(network_socket, message, (size_t)SIZE);

        if(char_count == -1){
            perror("Hubo un error al recibir el mensaje");
            exit(1);
        }
    }
    return 0;
}