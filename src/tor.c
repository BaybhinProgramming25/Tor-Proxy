#define _GNU_SOURCE
#include <dlfcn.h>

#include "../include/proxy_request.h"
#include "../include/proxy_response.h"


// Turn this into a shared library 
int connect(int sck2, const struct sockaddr* sck_struct, socklen_t addr_len) {

    // Make a function pointer to connect
    int (*orig_connect)(int, const struct sockaddr*, socklen_t);

    // Set this as a shared library 
    orig_connect = dlsym(RTLD_NEXT, "connect");

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
    if(orig_connect(fd, (struct sockaddr*)&proxy_addr, sizeof(proxy_addr)) < 0) {
        perror("Error connecting to SOCKS4 proxy\n");
        close(fd);
        return -1;
    }

    // Make a request
    // We need to grab the inputs directly when we are turning this into a shared library 
    proxy_request req = request((struct sockaddr_in *)sck_struct);
 
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
        printf("Successfully connected to SOCKS proxy\n");
    } else {
        printf("SOCKS proxy connection failed (response code: %u)\n", res.cd);
        close(fd);
        return -1;
    }

    // gcc tpn.c -o tpn.so -fPIC -shared -ldl -D_GNU_SOURCE
    dup2(fd, sck2); 
    return 0;

}
