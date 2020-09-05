#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <arpa/inet.h>
#include <error.h>

#define DEBUG 1

int main(int argc, char* argv[])
{
    int portProvided = 0;
    int sockProvided = 0;
    int opt;
    int port;
    int sockDesc;
    struct sockaddr_in serverAddr;
    struct in_addr se_addr;
    socklen_t addr_size;

    while ((opt = getopt(argc, argv, "p:d:")) != -1)
    {
        switch(opt)
        {
            case 'p':
                portProvided = 1;
                port = atoi(optarg);
                break;
            case 'd':
                sockProvided = 1;
                sockDesc = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-p] port number [-d] file descriptor\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if(!portProvided || !sockProvided)
    {
        fprintf(stderr, "Usage: %s [-p] port number [-d] file descriptor\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(DEBUG)
        printf("Port number: %d, File descriptor: %d\n", port,socket);
    
    if( inet_aton("127.0.0.1", &se_addr) == 0 )
    {
        fprintf(stderr, "Inet error, wrong ip address\n");
        exit(EXIT_FAILURE);
    }
    
    sockDesc = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = port;
    serverAddr.sin_addr = se_addr;
    
    addr_size = sizeof(struct sockaddr_in);

    if( connect(sockDesc, (struct sockaddr *)  &serverAddr, sizeof(struct sockaddr_in)) == -1)
    {
        perror("Error connecting");
        exit(EXIT_FAILURE);
    }

    printf("Connected successfully\n");

    return 1;
}

