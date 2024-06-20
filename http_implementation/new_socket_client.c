#include <stdio.h>
#include <stdlib.h>

#include <sys/sockets.h>
#include <sys/types.h>

#include <netinet/in.h>

int main () {
    
    // create socket
    int my_home_socket = socket(AF_INET, SOCK_DGRAM, 0);

    // connect this socket to my home ip on this machine's ip (172.30.142.35)
    struct sockaddr_in foreign_address;
    foreign_address.sin_family = AF_INET;
    foreign_address.sin_port = htons(8080);
    foreign_address.in_addr.sin_addr = 

}