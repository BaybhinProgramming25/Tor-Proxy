#include "../include/proxy_response.h"


// Receive a response 
int receive_response(int fd, proxy_response* res) {
    ssize_t bytes_read = read(fd, res, sizeof(*res));
    if (bytes_read < 0) {
        perror("Failed to read request");
        return -1;
    }
    return 0;
}