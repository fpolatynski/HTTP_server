#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include "server.h"


int main(void) {

    // Create a socket
    int server_socket = create_socket();
    struct sockaddr client_addr;

    socklen_t adress_len = sizeof(client_addr);
    const char *response_ok = "HTTP/1.1 200 OK\r\n\r\n";
    const char *response_not_found = "HTTP/1.1 404 Not Found\r\n\r\n";

    while (1) {
        int fd = accept(server_socket, &client_addr, &adress_len);
        if (fd < 0) {
            printf("Error accepting connection\n");
            continue;
        }
        printf("Connection accepted\n");

        char buffer[1024];
        read(fd, buffer, sizeof(buffer));
        char* request_type = strtok(buffer, " ");
        char* request_path = strtok(NULL, " ");
        printf("Request type: %s to path: %s\n", request_type, request_path);

        if (strcmp(request_path, "/") == 0) {
            write(fd, response_ok, strlen(response_ok));
        } else {
            write(fd, response_not_found, strlen(response_not_found));
        }

        close(fd);
    }

    // Close the socket
    close(server_socket);

}