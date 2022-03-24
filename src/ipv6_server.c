#include "dependencies.h"

int main(int argc, char* argv[]){
    int listen_socket, new_socket;
    struct sockaddr_in6 server_address, client_address;
    socklen_t client_address_length;
    //char message[INET6_ADDRSTRLEN];
    int pid;
    ssize_t char_count;

    if(argc<2){
        fprintf(stderr, "Ingrese un valor de puerto\n");
        exit(1);
    }

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

    int puerto = atoi(argv[1]);
    server_address.sin6_family = AF_INET6;
    server_address.sin6_addr = in6addr_loopback;
    server_address.sin6_port = htons((uint16_t)puerto);

    if(bind(listen_socket, (struct sockaddr*) &server_address, sizeof(server_address)) == -1){
        perror("Error al hacer el binding");
        exit(1);
    }
    signal(SIGCHLD, SIG_IGN);

    printf("ᴍᴏꜱʜɪ ᴍᴏꜱʜɪ!\n[IPV6] Servidor: PID %d - Socket disponible en puerto %d\n", getpid(), ntohs(server_address.sin6_port));

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

    
