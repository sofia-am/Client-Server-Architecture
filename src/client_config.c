#include "client_config.h"

int ipv4_client(char argv[]){
    int SIZE = atoi(argv[3]);

    if(SIZE>MAX_SIZE){
        printf("Ingrese un tamaño menor a 1024");
        exit(1);
    }

    char message[SIZE]; // string donde almacenamos la respuesta
    //socket_data.ipv4_size = SIZE; //seteo en la estructura compartida entre el cliente y el servidor el tamaño de buffer a utilizar

    ssize_t char_count; //nos dice cuantos caracteres fueron escritos/leídos con éxito
    int network_socket;
/*
    if(argc<3){
        fprintf(stderr, "Ingrese un host y un puerto\n");
        exit(0);
    }
*/
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

    while(1){
        memset(message, 'a', (size_t)SIZE);
        
        char_count = write(network_socket, message, strlen(message));

        if(char_count == -1){
            perror("Hubo un error al enviar el mensaje");
            exit(1);
        }
    }
    return 0;
}

int ipv6_client(char argv[]){
    int network_socket;
    struct sockaddr_in6 server_address;
    int connection_status;
    ssize_t char_count;
    
    int SIZE = atoi(argv[3]);

    if(SIZE>MAX_SIZE){
        printf("Ingrese un tamaño menor a 1024\n");
        exit(1); 
    }
    char message[SIZE];

/*
    if(argc<2){
        printf("Por favor, ingrese puerto y host");
        exit(0);
    }
*/
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
    memset(message, 'a', (size_t)SIZE);
    while(1){

        char_count = write(network_socket, message, strlen(message));

        if(char_count == -1){
            perror("Hubo un error al enviar el mensaje");
            exit(1);
        }
    }
    return 0;


}


int unix_client(char argv[]){
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
/*
    if(argc<2){
        fprintf(stderr, "Debe ingresar un archivo como parámetro\n");
        exit(0);
    }
*/

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

        char_count = write(local_socket, message, strlen(message));

        if(char_count < 0){
            perror("Error en la escritura del socket");
            exit(1);
        }
    }
    return 0;
}