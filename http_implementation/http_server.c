#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

const int MY_PORT = 60000;

int main() {

    printf("starting program...\n");
    fflush(stdout); // Flush the output buffer... flush means to force all text print immediately 

    // open a file to serve and read it to a buffer
    FILE* html_data;
    html_data = fopen("./index.html", "r"); // index.html is the response body, "r" means reading from file

    if (html_data == NULL) {
        printf("the file didn't open\n");
        fflush(stdout); 
    } else {
        printf("the file opened\n");
        fflush(stdout); 
    }

    char response_data[1024];

    // read the entire, multi-line file

    char* source = NULL; 
    if (fseek(html_data, 0L, SEEK_END) == 0) { // move the pointer to the end of the file, returns 0 if successful, hence the if-statement
        long buff_size = ftell(html_data); // ftell tells us how long the file is IF the pointer is at the end of the file 
        source = malloc(sizeof(buff_size + 1)); // get memory for the size of the buffer/size of the file itself 

        if (fseek(html_data, 0L, SEEK_SET) == 0) { // brings pointer to beginning of the file (SEEK_SET) and start reading the file from there 
            size_t newLen = fread(source, sizeof(char), buff_size, html_data); // fread returns a size_t, which is the num of elements that are read succesfully from the file
            // fread() writes the memory from the file into the buffer, in this case "source", the sizeof(char) parameter tells us the size of each element in the file
        }
    }

    fclose(html_data); // close file

    

    // fgets(response_data, 1024, html_data); // (where you're reading to, how much space are you reading to, where you're reading from)

    // ----------------------------------------------------

    char http_header[2048] = "HTTP/1.1 200 OK\r\n\n"; // the response header that lets the client know that the response is OK and there are no errors
    // char different_header[1023] = "HTTP/3.0 401 Unauthorized\r\n\n";

    strcat(http_header, source); // adding data from response_data INTO in the http_header

    // creeate a socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(MY_PORT); // htons() converts the port number into a different format so that the server_address structure can understand it
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    listen(server_socket, 5);

    int client_socket;

    printf(
        "This server's address information is: \n socket info: %d\ns port info: %d\n server ip: %d", 
        server_socket, MY_PORT, server_address.sin_addr.s_addr);

    while (1) {
        client_socket = accept(server_socket, NULL, NULL);
        send(client_socket, http_header, sizeof(http_header), 0);
        // send(client_socket, different_header, sizeof(different_header), 0);
        close(client_socket);
    }

    free(source);

    return 0;
}

