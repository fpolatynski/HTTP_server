#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

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

    // Create Threads
    pthread_t threads[THREADS];
    int short thread_status[THREADS] = {0};

    while(1) {
        for (int i = 0; i < THREADS; i++) {
            if (thread_status[i] == 0) {
                int client_socket = accept(server_socket, &client_addr, &adress_len);
                printf("%d", client_socket);
                struct connection *con = malloc(sizeof(struct connection));
                con->client_socket = client_socket;
                con->response = response;
                con->response_not_found = response_not_found;
                if (pthread_create(&threads[i], NULL, handle_connection, (void *) con) != 0) {
                    printf("Error creating thread\n");
                    return -1;
                }
                thread_status[i] = 1;
            }
        }
        for (int i = 0; i < THREADS; i++) {
            if (thread_status[i] == 1) {
                pthread_join(threads[i], NULL);
                thread_status[i] = 0;
            }
        }
    }
    
    // Close the socket
    free(response_not_found);
    free(response);
    close_socket(server_socket);
    return 0;

}