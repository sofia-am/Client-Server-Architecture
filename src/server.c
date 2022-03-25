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

    int sec = 0;
    char log[10000];
    time_t time_;
    char logtime[80];
    system("touch log.txt");
    int logger = open("log.txt", O_WRONLY);

    while(1){
        struct tm *timestamp;
        sec++;
        time(&time_);
        strftime(logtime, 80, "%x - %X", timestamp);
        sprintf(log, "%s\nIPV4 bandwidth: %ld Mbits/s\nIPV6 bandwidth %ld Mbit/s\nUnix bandwidth: %ld Mbits/s", timestamp,
        ((bytes->ipv4_bytes/sec)*8/100000, (bytes->ipv6_bytes/sec)*8/100000), (bytes->unix_bytes/sec)*8/100000);
        long int total = ((bytes->ipv4_bytes) + (bytes->ipv6_bytes) + (bytes->unix_bytes))/sec;

        write(logger, log, strlen(log));
        printf("%s ", log);
        sleep(1);

    }
    return 0;


}