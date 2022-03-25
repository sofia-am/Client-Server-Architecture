#include "server_config.h"

int main(int argc, char* argv[]){
    int pid;
    
    data *bytes;
    int shared_mem = shmget(ftok(".", 'S'), sizeof(bytes), (IPC_CREAT | 0660));
    if(shared_mem < 0){
        perror("Shared Memory: Error");
        exit(1);
    }

    bytes = shmat(shared_mem, 0, 0);
    if(bytes == (void *)-1){
        perror("Error al asignar memori");
        exit(1);
    }else{
        printf("Shared Memory: Available \n\n");
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

    int aux;
    int promedio;
    long int ipv4_bw;
    long int ipv6_bw;
    long int unix_bw;
    char* info = malloc(50);
    int stat;

    

    while(1){
        FILE *log = fopen("log.txt", "a");
        ipv4_bw = (bytes->ipv4_bytes/8);
        ipv6_bw = (bytes->ipv6_bytes/8);
        unix_bw = (bytes->unix_bytes/8);
        printf(" \n");

        sleep(1);
        stat = sprintf(info, "IPV4: %ld\tIPV6: %ld\tUNIX: %ld\t", ipv4_bw, ipv6_bw, unix_bw);

        if(stat < 0){
            perror("Error al generar string");
            exit(1);
        }

        stat = fprintf(log, "IPV4: %ld\tIPV6: %ld\tUNIX: %ld\t\n", ipv4_bw, ipv6_bw, unix_bw);
        //stat = fprintf(log, info);
        //fclose(log);
        if(stat < 0){
            perror("Error al escribir en el archivo");
            exit(1);
        }
        printf("%s", info);
        fclose(log);
    }
/*
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
*/
}