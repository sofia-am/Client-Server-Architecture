#include "server_config.h"

int main(int argc, char* argv[]){
    int pid;
    
    if(argc<3){
        perror("Por favor ingrese los valores de los puertos en el orden:\n<IPV4> <IPV6> <UNIX>");
    }

    pid = fork();
    if(pid == -1){
        perror("Error al crear el nuevo proceso");
        exit(1);
    }else if(pid == 0){
        ipv4_server(argv[1]);
    }

    pid = fork();
    if(pid == -1){
        perror("Error al crear el nuevo proceso");
        exit(1);
    }else if(pid == 0){
        ipv6_server(argv[2]);
    }
    
    pid = fork();
    if(pid == -1){
        perror("Error al crear el nuevo proceso");
        exit(1);
    }else if(pid == 0){
        unix_server(argv[3]);
    }


}