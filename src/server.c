#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#include "server.h"
#include "utils.h"

int init_server() {

    //Create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket < 0) {
        printf("Error creating socket\n");
        return -1;
    }

    // Create a server address
    struct sockaddr_in server_address = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr.s_addr = INADDR_ANY
    };

    // Bind the socket to the address
    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        printf("Error binding socket\n");
        return -1;
    }

    int backlog = 5;
    // Listen for incoming connections
    if (listen(server_socket, backlog) < 0) {
        printf("Error listening on socket\n");
        return -1;
    }

    printf("Listening on port %d\n", PORT);

    return (server_socket);
}


void handle_connection(int server_socket) {
    struct sockaddr client_addr;

    socklen_t adress_len = sizeof(client_addr);
    char* html = parse_html("templates/index.html");
    if (html == NULL) {
        printf("Error reading html file\n");
        free(html);
        return;
    }
    char *response_ok = "HTTP/1.1 200 OK\r\nContent-Type:text/html\r\n\r\n";
    char *response = malloc(strlen(response_ok) + strlen(html));
    strcpy(response, response_ok);
    strcat(response, html);
    free(html);
    const char *response_not_found = "HTTP/1.1 404 Not Found\r\nContent-Type:text/html\r\n\r\n<html><body><h1>404 Not Found</h1></body></html>";

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
            write(fd, response, strlen(response));
        } else {
            write(fd, response_not_found, strlen(response_not_found));
        }
        close(fd);
    }
    free(response);
}

void close_socket(int server_socket) {
    close(server_socket);
}
