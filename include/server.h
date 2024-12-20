#ifndef SERVER_H
#define SERVER_H

#define PORT 9002
#define BACKLOG 10

// Conection functions
int init_server();
void* handle_connection(void *arg);
void close_socket(int server_socket);

// Functions generating HTTP/1.1 responses
char* not_found_response();
char* index_response();

#endif