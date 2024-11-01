#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include<string.h>


int main(void) {

    //Create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr client_addr;

    if (server_socket < 0) {
        printf("Error creating socket\n");
        return 1;
    }

    // Create a server address
    struct sockaddr_in server_address = {
        .sin_family = AF_INET,
        .sin_port = htons(9002),
        .sin_addr.s_addr = INADDR_ANY
    };

    // Bind the socket to the address
    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        printf("Error binding socket\n");
        return 1;
    }

    int backlog = 5;
    // Listen for incoming connections
    if (listen(server_socket, backlog) < 0) {
        printf("Error listening on socket\n");
        return 1;
    }

    printf("Listening on port 9002\n");

    socklen_t adress_len = sizeof(client_addr);

    while (1) {
        int fd = accept(server_socket, &client_addr, &adress_len);
        if (fd < 0) {
            printf("Error accepting connection\n");
            continue;
        }
        printf("Connection accepted\n");

        char buffer[1024];
        read(fd, buffer, sizeof(buffer));

        const char *response = "HTTP/1.1 200 OK\r\n\r\n";
        write(fd, response, strlen(response));

        close(fd);
    }

    // Close the socket
    close(server_socket);

}