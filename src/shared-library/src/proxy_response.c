#include "../include/proxy_response.h"


// Receive a response 
int receive_response(int fd, proxy_response* res) {


    ssize_t totalBytesRead = 0; 
    ssize_t count = sizeof(*res);

    while(totalBytesRead < count) {
        ssize_t bytes_read = read(fd, res + totalBytesRead, count - totalBytesRead);

        if(bytes_read <= 0) {
            if(bytes_read == 0) {
                // EOF reached
                break;
            }
            if(errno == EINTR) {
                // Some signal error happen which may interrupt our sys call so we continue
                continue;
            }
        }
    }
    
    
    return 0;
}
