// Define our proxy_response struct
// We base this structure on the SOCKS4 Protocol
#ifndef PROXY_RESPONSE_H
#define PROXY_RESPONSE_H

#include <stdlib.h>
#include <arpa/inet.h>

struct ProxyResponse {
    unsigned char vn;
    unsigned char cd;
    unsigned short int dstPort;
    unsigned int dstIP;
};
typedef struct ProxyResponse Response; 

// Definr our response function

// Get the struct size
size_t structSizeResponse(void);


#endif 