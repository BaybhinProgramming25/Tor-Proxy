#include "../include/proxy_request.h"

// Implement request function
proxy_request request(const char *ip, const int port) {
    
    proxy_request req;

    req.vn = SOCKS_VERSION;
    req.cd = SOCKS_CD;
    req.dstip = inet_addr(ip);
    req.dstport = htons(port);
    req.userid[0] ='\0';

    return req; 
}

// Function to send the request
int send_request(int fd, proxy_request *req) {

    ssize_t bytes_written = write(fd, req, sizeof(*req));
    if (bytes_written < 0) {
        perror("Unable to send request");
        return -1;
    }
    return 0;
}