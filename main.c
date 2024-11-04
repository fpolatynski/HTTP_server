#include "server.h"


int main(void) {

    // Create a socket
    int server_socket = init_server();
    if(server_socket < 0) {
        return -1;
    }

    // Handle connections
    handle_connection(server_socket);
    
    // Close the socket
    close_socket(server_socket);
    return 0;

}