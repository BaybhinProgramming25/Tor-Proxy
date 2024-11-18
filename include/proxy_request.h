// Define our proxy_request struct
// We base this structure on the SOCKS4 Protocol
#ifndef PROXY_REQUEST_H
#define PROXY_REQUEST_H

#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>

#include "constants.h"

typedef struct {
    uint8_t vn;
    uint8_t cd;
    uint16_t dstport;
    uint32_t dstip;
    char userid[1]; // Set character length to 1 for now 
} proxy_request; 

// Define our request function
proxy_request request(struct sockaddr_in*);

// Send request function
int send_request(int, proxy_request*);


#endif 