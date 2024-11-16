#ifndef UTILS_H
#define UTILS_H

#define THREADS 10

struct connection {
    int client_socket;
    char* response;
    char* response_not_found;
};

char* parse_html(char* path);

#endif