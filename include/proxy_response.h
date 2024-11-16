// Define our proxy_response struct
// We base this structure on the SOCKS4 Protocol
#ifndef PROXY_RESPONSE_H
#define PROXY_RESPONSE_H

#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


#include "constants.h"

typedef struct {
    uint8_t vn;
    uint8_t cd;
    uint16_t dstport;
    uint32_t dstip;
} proxy_response; 

// Receive response function
int receive_response(int, proxy_response*);


#endif 