// Define our proxy_request struct
// We base this structure on the SOCKS4 Protocol
#ifndef PROXY_REQUEST_H
#define PROXY_REQUEST_H

#include <stdlib.h>
#include <arpa/inet.h>

struct ProxyRequest {
    unsigned char vn;
    unsigned char cd;
    unsigned short int dstPort;
    unsigned int dstIP; 
    char userid[2];
};
typedef struct ProxyRequest Request; 

// Define our request function
Request *request(const char *, const int);

// Get the size of our struct
size_t structSizeRequest(void);


#endif 