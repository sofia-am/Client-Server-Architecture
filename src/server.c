#include "server_config.h"

int main(int argc, char* argv[]){
    int pid;
    
    data *bytes;
    int shared_mem = shmget(ftok(".", 'S'), sizeof(bytes), (IPC_CREAT | 0660));
    if(shared_mem < 0){
        perror("Error al crear un segmento de memoria compartida");
        exit(1);
    }

    bytes = shmat(shared_mem, 0, 0);
    if(bytes == (void *)-1){
        perror("Error al asignar memori");
        exit(1);
    }else{
        printf("Se creó un segmento de memoria compartida \n");
    }

    signal(SIGCHLD, SIG_IGN);
    if(argc<3){
        perror("Por favor ingrese los valores de los puertos en el orden:\n<IPV4> <IPV6> <UNIX>");
        exit(0);
    }

    pid = fork();
    if(pid == -1){
        perror("Error al crear el nuevo proceso");
        exit(1);
    }else if(pid == 0){
        ipv4_server(argv[1], &(bytes->ipv4_bytes));
    }

    pid = fork();
    if(pid == -1){
        perror("Error al crear el nuevo proceso");
        exit(1);
    }else if(pid == 0){
        ipv6_server(argv[2], &(bytes->ipv6_bytes));
    }
    
    pid = fork();
    if(pid == -1){
        perror("Error al crear el nuevo proceso");
        exit(1);
    }else if(pid == 0){
        unix_server(argv[3], &(bytes->unix_bytes));
    }


}