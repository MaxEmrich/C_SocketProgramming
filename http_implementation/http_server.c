#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

const int MY_PORT = 60000;

int main() {

    // open a file to serve 
    FILE* html_data;
    html_data = fopen("index.html", "r"); // index.html is the response body, "r" means reading from file

    char response_data[1024];
    fgets(response_data, 1024, html_data); // (where you're reading to, how much space are you reading to, where you're reading from)

    char http_header[2048] = "HTTP/1.1 200 OK\r\n\n"; // the response header that lets the client know that the response is OK and there are no errors

    strcat(http_header, response_data); // adding data from response_data INTO in the http_header

    // creeate a socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(MY_PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    listen(server_socket, 5);

    int client_socket;

    while (1) {
        client_socket = accept(server_socket, NULL, NULL);
        send(client_socket, http_header, sizeof(http_header), 0);
        close(client_socket);
    }
    return 0;
}

