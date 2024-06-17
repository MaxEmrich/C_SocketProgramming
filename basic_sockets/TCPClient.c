#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
// this is TCP connection

int main () {

    // create a socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0); //params are socket(domain, socket stream (type of socket, TCP vs UDP or datagram), protocal)
    // this network socket is one of the endpoints needed to create a network communication
    // we will create another socket that we can interact with (send or receive data to/from)

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; // the family of addresses, which is INET
    server_address.sin_port = htons(9002); // this specifies the port number, htons is for converting port integer num to the correct data format
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address)); // returns an integer that lets us know if the connection was successful or not
    if (connection_status == -1) {
        printf("error!\n");
    } else {
        printf("everything is okay with the connection\n");
    }

    // recieve data from the server
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0); // params are socket, recieving data buffer, sizeof recieving data, and optional flags param

    // print out the data that we get back from the server/the server's response 
    printf("the server sent the data: %s\n", server_response);
    close(network_socket); // closes the connection of the socket
    return 0;

}