#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>


#include "../include/proxy_request.h"
#include "../include/proxy_response.h"


int main(int argc, char *argv[]) {

    // Check to see if we pass in the correct number of arguments
    if (argc < 3) {
        fprintf(stderr, "Insufficent arguments provided. Please provide: <host> & <port>");
        return -1;
    }

    // Initialization
    char *hostname = NULL;
    int port = -1;

    // Set respective variables to the ones in argc
    hostname = argv[1];
    port = atoi(argv[2]);


    // 1) Create socket
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0) {
        fprintf(stderr, "Error in creating socket");
        return -1;
    }

    // Define our socket struct
    struct sockaddr_in socket;
    memset(&socket, 0, sizeof(socket));
    socket.sin_family = AF_INET;
    socket.sin_port = htons(9050); // Tor runs on this port
    socket.sin_addr.s_addr = inet_addr("127.0.0.1"); // Loop back address

    // Connect 
    if(connect(fd, (struct sockaddr *)&socket, sizeof(socket)) < 0) {
        fprintf(stderr, "Error in connecting");
        close(fd);
        return -1; 
    }

    // Begin making our request 
    Request *req;
    req = request(hostname, port);
    if(req == NULL) {
        close(fd);
        return -1; 
    }


    // Make write system call
    size_t req_side = structSizeRequest();
    write(fd, req, req_side);

    
    uint8_t response[8];
    if(read(fd, response, sizeof(response)) < 0) {
        fprintf(stderr, "Error in reading");
        free(req);
        close(fd);
        return -1;
    }

    if(response[1] == 90) {
        fprintf(stdout, "CD equals 90");
    }

    printf("%u\n", response[0]);
    printf("%u\n", response[1]);

 

    // Clean up once we are done 
    free(req); 
    close(fd);
    return 0;

}