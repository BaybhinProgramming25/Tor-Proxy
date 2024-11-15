#include "../include/proxy_response.h"

// Response might not need an implementation 


// Get struct size response
size_t structSizeResponse(void) {

    size_t vn_size = sizeof(unsigned char);
    size_t cd_size = sizeof(unsigned char);
    size_t dst_port_size = sizeof(unsigned short int);
    size_t dst_ip_size = sizeof(unsigned int);

    size_t sum = vn_size + cd_size + dst_port_size + dst_ip_size;
    return sum;

}