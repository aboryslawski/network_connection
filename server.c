#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>
#include <arpa/inet.h>
#include <errno.h>

#define DEBUG 1
#define MAX_CON 100

int main(int argc, char* argv[])
{
        int portProvided = 0;
        int opt;
        int port;
        int fileDesc;
        struct sockaddr_in myAddr;
        struct in_addr s_addr;
        socklen_t addr_size;

        while ((opt = getopt(argc, argv, "p:")) != -1)
        {
            switch (opt) 
            {
                case 'p':
                    portProvided = 1;
                    port = atoi(optarg);
                    break;
                default:
                    fprintf(stderr, "Usage: %s [-p] port number\n", argv[0]);
                    exit(EXIT_FAILURE);
            }
        }
        
        if (!portProvided)
        {
            fprintf(stderr, "Usage: %s [-p] port number\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        
        if(DEBUG)
            printf("Port number: %d\n", port);

        fileDesc = socket(AF_INET, SOCK_STREAM, 0);
        int optVal = 1;

        setsockopt(fileDesc, SOL_SOCKET, SO_REUSEADDR, (const void *)&optVal, sizeof(int));

        if(fileDesc == -1)
        {
            fprintf(stderr, "Error creating socket\n");
            exit(EXIT_FAILURE);
        }

        if(DEBUG)
            printf("Socket file descriptor: %d\n", fileDesc);
        
        //s_addr.s_addr = "192.168.0.1";
        if( inet_aton("127.0.0.1", &s_addr) == 0)
        {
            fprintf(stderr, "Inet error, wrong ip address\n");
            exit(EXIT_FAILURE);
        }

        myAddr.sin_family = AF_INET;
        myAddr.sin_port = port;
        myAddr.sin_addr = s_addr;
        
        if(bind(fileDesc, (struct sockaddr *) &myAddr, sizeof(struct sockaddr_in)) == -1)
        {
            perror("Error binding");
            exit(EXIT_FAILURE);
        }
        
        if(listen(fileDesc, MAX_CON) == -1)
        {
            perror("Error listening");
            exit(EXIT_FAILURE);
        }
        
        addr_size = sizeof(struct sockaddr_in);
        
        if(accept(fileDesc, (struct sockaddr *) &myAddr, &addr_size) == -1)
        {
            perror("Accept");
            exit(EXIT_FAILURE);
        }

        if(DEBUG)
            printf("Accepted connection\n");

        return 1;
}
