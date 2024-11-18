#include "../include/proxy_request.h"

// Implement request function
proxy_request request(struct sockaddr_in* sck) {
    
    proxy_request req;
    memset(&req, 0, sizeof(req));

    req.vn = SOCKS_VERSION;
    req.cd = SOCKS_CD;
    req.dstport = sck->sin_port;
    req.dstip = sck->sin_addr.s_addr; 
    req.userid[0] ='\0';

    return req; 
}

// Function to send the request
int send_request(int fd, proxy_request *req) {


    size_t totalBytesWritten = 0;
    size_t count = sizeof(*req);
    while(totalBytesWritten < count) {
        ssize_t bytes_written = write(fd, req + totalBytesWritten, count - totalBytesWritten);

        if(bytes_written <= 0) {
            if(bytes_written == 0){
                // EOF most likely reached
                break;
            }
            if(errno == EINTR) {
                // Some error happened, but we still continue 
                continue;
            }
            perror("Unable to send request");
            return -1; 
        }
        totalBytesWritten += bytes_written; 
    } 
    
    return 0; 
}