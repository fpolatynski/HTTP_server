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

    // Listen for incoming connections
    if (listen(server_socket, BACKLOG) < 0) {
        printf("Error listening on socket\n");
        return -1;
    }

    printf("Listening on port %d\n", PORT);

    return server_socket;
}

void* handle_connection(void *arg) {
    struct connection *con = (struct connection *) arg;
    if (con->client_socket < 0) {
            printf("Error accepting connection\n");
            free(con);
            return NULL;
        }
    printf("Connection accepted\n");

    char buffer[1024];
    read(con->client_socket, buffer, sizeof(buffer));
    printf("Request: %s\n", buffer);
    char* request_type = strtok(buffer, " ");
    char* request_path = strtok(NULL, " ");
    printf("Request type: %s to path: %s\n", request_type, request_path);

    if (strcmp(request_path, "/") == 0) {
        write(con->client_socket, con->response, strlen(con->response));
    } else {
        write(con->client_socket, con->response_not_found, strlen(con->response_not_found));
    }
    close(con->client_socket);
    free(con);
    return NULL;
}


char* index_response() {
    char* html = parse_html("templates/index.html");
    if (html == NULL) {
        printf("Error reading html file\n");
        free(html);
        return NULL;
    }
    char *response_ok = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: ";

    char *content_lenght = malloc(8);
    sprintf(content_lenght, "%lu", strlen(html));

    char *response = malloc(strlen(response_ok) + strlen(html) + 8 + 4);
    strcpy(response, response_ok);
    strcat(response, content_lenght);
    strcat(response, "\r\n\r\n");
    strcat(response, html);

    free(html);
    free(content_lenght);
    return response;
}


char* not_found_response() {
    char *response_not_found = "HTTP/1.1 404 Not Found\r\nContent-Type:text/html\r\n\r\n<html><body><h1>404 Not Found</h1></body></html>";
    return response_not_found;
}


void close_socket(int server_socket) {
    close(server_socket);
}
