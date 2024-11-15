#include "../include/proxy_request.h"

// Implement our request function
Request *request(const char *destIP, const int destPort) {

    // Initialize our request
    Request *request;

    request = (Request*)malloc(sizeof(Request));

    if(request == NULL) {
        free(request);
        return NULL;
    }

    request->vn = 4; 
    request->cd = 1;
    request->dstPort = htons(destPort);
    request->dstIP = inet_addr(destIP);
    request->userid[1] = '\0';

    return request;

}

// Get the size of our struct
size_t structSizeRequest() {

    size_t vn_size = sizeof(unsigned char);
    size_t cd_size = sizeof(unsigned char);
    size_t dst_port_size = sizeof(unsigned short int);
    size_t dst_ip_size = sizeof(unsigned int);

    size_t sum = vn_size + cd_size + dst_port_size + dst_ip_size;
    return sum;
    
}