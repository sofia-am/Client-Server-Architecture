#include "dependencies.h"
#define SIZE 80

int main(int argc, char *argv[]){
    int local_socket, new_local_socket, pid;
    socklen_t server_length, client_length;
    ssize_t char_count, bind_status;
    struct sockaddr_un server_address, client_address;

    char message[MAX_SIZE];

    if(argc<2){
        printf("Debe asignarle un nombre al socket como parámetro");
        exit(0);
    }

    local_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    if(local_socket == -1){
        perror("Error en la creación del socket");
        exit(1);
    }

    unlink(argv[1]);

    memset((void*)&server_address, 0, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, argv[1]); //almaceno el nombre del socket que pasé como parametro
    server_length = (socklen_t)(strlen(server_address.sun_path)+sizeof(server_address.sun_family));

    bind_status = bind(local_socket, (struct sockaddr*)&server_address, server_length);

    if(bind_status == -1){
        perror("Error al hacer el bind");
        exit(1);
    }

    printf("ᴍᴏꜱʜɪ ᴍᴏꜱʜɪ!\n[UNIX] Servidor: PID %d - Socket disponible en socket %s\n", getpid(), server_address.sun_path);
    listen(local_socket, 5);
    client_length = sizeof(client_address);
    signal(SIGCHLD, SIG_IGN);

    while(1){
        new_local_socket = accept(local_socket, (struct sockaddr*)&client_address, &client_length);

        pid = fork();

        if(pid == 0){
            close(local_socket);

            while(1){
                memset(message, 0, (size_t)MAX_SIZE);

                char_count = read(new_local_socket, message, SIZE-1);

                if(char_count < 0){
                    perror("Error en la lectura del socket");
                    exit(1);
                }

                //printf("PROCESO %d ", getpid());
                //printf("Recibí: %s", message);

                char_count = write(new_local_socket, "Obtuve su mensaje ", 18);
                
                if(char_count < 0){
                    perror("Error en la escritura del socket");
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