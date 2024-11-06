#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#include "server.h"
#include "utils.h"



int main(void) {

    // Create a socket
    int server_socket = init_server();
    if(server_socket < 0) {
        return -1;
    }

    // Create a client address
    struct sockaddr client_addr;
    socklen_t adress_len = sizeof(client_addr);

    // Generate the HTTP/1.1 responses
    char* response = index_response();
    char* response_not_found = not_found_response();

    while(1) {
        int client_socket = accept(server_socket, &client_addr, &adress_len);
        handle_connection(client_socket, response, response_not_found);
        
    }
    
    // Close the socket
    free(response);
    close_socket(server_socket);
    return 0;

}