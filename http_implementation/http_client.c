#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>


int main (int argc, char *argv[]) {

    char* address;
    address = argv[1];

    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // connect to an address
    struct sockaddr_in remote_address;
    remote_address.sin_family = AF_INET;
    remote_address.sin_port = htons(80);
    
    
    if (inet_aton(address, &remote_address.sin_addr.s_addr) == 0)  { // inet_aton converts from IPv4 numbers-and-dots notation into network byte order 
        printf("Invalid address\n");
        return 1; 
    }

    connect(client_socket, (struct sockaddr*) &remote_address, sizeof(remote_address)); // requests a connection from a foreign host, connecting with "client_socket"

    char request[] = "GET / HTTP/1.1\r\n\r\n";
    char response[8000];

    send(client_socket, request, sizeof(request), 0);
    recv(client_socket, &response, sizeof(response), 0);

    printf("response from the server: %s\n", response);

    // size_t len = sizeof(my_address); // size_t can hold the largest object size in memory on any OS
    // printf("size of my_address is: %d\n", len);

    close(client_socket);

    return 0;
}