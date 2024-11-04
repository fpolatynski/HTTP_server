#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

char* parse_html(char* path) {
    FILE *html = fopen(path, "r");
    if (html == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    fseek(html, 0, SEEK_END);
    long length = ftell(html);
    fseek(html, 0, SEEK_SET);
    char *buffer = malloc(length + 1);

    if (buffer == NULL) {
        fclose(html);
        return NULL;
    }
    fread(buffer, 1, length, html);
    buffer[length] = '\0';
    fclose(html);
    return buffer;
}