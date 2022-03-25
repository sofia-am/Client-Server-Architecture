#include "server_config.h"

int ipv4_server(char argv[], long int *bytes){
    int pid1, new_server_socket, server_socket;
    ssize_t char_count = 0;
    struct sockaddr_in server_address, client_address;
/*
    if(argc<2){
        fprintf(stderr, "Ingrese un valor de puerto\n");
        exit(1);
    }
*/
    // creamos el socket de servidor
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(server_socket == -1){
        perror("Error en la apertura del socket");
        exit(1);
    }

    // definimos la direccion del servidor
    memset((char*)&server_address, '0', sizeof(server_address));

    int puerto = atoi(argv); //el nro de puerto es pasado como argumento
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons((uint16_t)puerto);
    server_address.sin_addr.s_addr = INADDR_ANY;
    //memset(&(server_address.sin_zero), '\0', 8);

    //bindeamos el socket a nuestro puerto ip especificado
    if(bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) == -1){
        perror("Error al hacer el binding");
        exit(1);
    }

    printf("[IPV4] Servidor: PID %d - Socket disponible en puerto %d\n", getpid(), ntohs(server_address.sin_port));
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
                *bytes = char_count;
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


int ipv6_server(char argv[], long int *bytes){
    int listen_socket, new_socket;
    struct sockaddr_in6 server_address, client_address;
    socklen_t client_address_length;
    //char message[INET6_ADDRSTRLEN];
    int pid;
    ssize_t char_count;
/*
    if(argc<2){
        fprintf(stderr, "Ingrese un valor de puerto\n");
        exit(1);
    }
*/
    listen_socket = socket(AF_INET6, SOCK_STREAM, 0);
    if(listen_socket == -1){
        perror("Error al crear el socket");
        exit(1);
    }

    /* set socket to reuse address*/
    int flag = 1;
	int ret = setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
	if(ret == -1) {
		perror("setsockopt()");
		return EXIT_FAILURE;
	}

    memset((char*)&server_address, '0', sizeof(server_address));

    int puerto = atoi(argv);
    server_address.sin6_family = AF_INET6;
    server_address.sin6_addr = in6addr_loopback;
    server_address.sin6_port = htons((uint16_t)puerto);

    if(bind(listen_socket, (struct sockaddr*) &server_address, sizeof(server_address)) == -1){
        perror("Error al hacer el binding");
        exit(1);
    }
    signal(SIGCHLD, SIG_IGN);

    printf("[IPV6] Servidor: PID %d - Socket disponible en puerto %d\n", getpid(), ntohs(server_address.sin6_port));

    listen(listen_socket, 5);

    client_address_length = sizeof(client_address);

    if(client_address_length == 0){
        perror("Error en la dirección");
        exit(1);
    }

    while(1){
        new_socket = accept(listen_socket, (struct sockaddr*)&client_address, &client_address_length);
        if(new_socket == -1){
            perror("Error al generar un nuevo socket");
            exit(1);
        }

        pid = fork();

        if(pid == 0){
            close(listen_socket);

            while(1){
                
                char message[MAX_SIZE];
                memset(message, 0, (size_t)MAX_SIZE);
                
                char_count = read(new_socket, message, (size_t)MAX_SIZE-1);
                *bytes = char_count;
                if(char_count == -1){
                    perror("Error en la lectura del socket");
                    exit(1);
                }
            }
        }else{
                printf("[IPV6] PID %d - Atendiendo un nuevo cliente\n", pid);
                close(new_socket);
        }
    }
    return 0;
}


int unix_server(char argv[], long int *bytes){
    int local_socket, new_local_socket, pid;
    socklen_t server_length, client_length;
    ssize_t char_read, bind_status;
    struct sockaddr_un server_address, client_address;

    char message[MAX_SIZE];
/*
    if(argc<2){
        printf("Debe asignarle un nombre al socket como parámetro");
        exit(0);
    }
*/

    local_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    if(local_socket == -1){
        perror("Error en la creación del socket");
        exit(1);
    }

    unlink(argv);

    memset((void*)&server_address, 0, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, argv); //almaceno el nombre del socket que pasé como parametro
    server_length = (socklen_t)(strlen(server_address.sun_path)+sizeof(server_address.sun_family));

    bind_status = bind(local_socket, (struct sockaddr*)&server_address, server_length);

    if(bind_status == -1){
        perror("Error al hacer el bind");
        exit(1);
    }

    printf("[UNIX] Servidor: PID %d - Socket disponible en socket %s\n", getpid(), server_address.sun_path);
    listen(local_socket, 5);
    client_length = sizeof(client_address);


    while(1){
        new_local_socket = accept(local_socket, (struct sockaddr*)&client_address, &client_length);

        pid = fork();

        if(pid == 0){
            close(local_socket);

            while(1){
                memset(message, 0, (size_t)MAX_SIZE);

                char_read = read(new_local_socket, message, MAX_SIZE-1);
                *bytes = char_read;
                if(char_read < 0){
                    perror("Error en la lectura del socket");
                    exit(1);
                }
            }
        }else{
            printf("[UNIX] PID %d - Atendiendo un nuevo cliente\n", pid);
            close(new_local_socket);
        }
    }
    return 0;
}   