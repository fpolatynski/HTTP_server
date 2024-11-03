#ifndef SERVER_H
#define SERVER_H

#define PORT 9002

int init_server();
void handle_connection(int server_socket);

#endif