#include "../include/proxy_request.h"
#include "../include/proxy_response.h"


int main(int argc, char *argv[]) {
    // Check arguments
    if (argc < 3) {
        fprintf(stderr, "Insufficient arguments provided. Please provide: <host> & <port>\n");
        return -1;
    }

    // Initialization
    char *hostname = argv[1];
    int port = atoi(argv[2]);

    // Create socket
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        fprintf(stderr, "Error in creating socket\n");
        return -1;
    }

    // Define our socket struct
    struct sockaddr_in proxy_addr;
    memset(&proxy_addr, 0, sizeof(proxy_addr));
    proxy_addr.sin_family = AF_INET;
    proxy_addr.sin_port = htons(9050);  // Use the port from command line
    proxy_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect
    if(connect(fd, (struct sockaddr*)&proxy_addr, sizeof(proxy_addr)) < 0) {
        perror("Error connecting to SOCKS4 proxy\n");
        close(fd);
        return -1;
    }

    // Make a request
    proxy_request req = request(hostname, port);
 
    // Send request
    if(send_request(fd, &req) < 0) {
        close(fd);
        return -1;
    }

    // Construct response
    proxy_response res;
    if(receive_response(fd, &res)) {
        close(fd);
        return -1;
    }

    printf("Response code: %u\n", res.cd);
    if (res.cd == SOCKS_REQUEST_GRANTED) {
        printf("Successfully connected to %s:%d through SOCKS proxy\n", 
               hostname, port);
    } else {
        printf("SOCKS proxy connection failed (response code: %u)\n", res.cd);
        close(fd);
        return -1;
    }

    // Clean up
    close(fd);
    return 0;
   
}
