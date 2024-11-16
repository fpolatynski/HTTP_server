CC = gcc
CFLAGS = -Wall -g
INCLUDES = -I./include
SRCS = main.c src/server.c src/utils.c


all: build/main

build/main: $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o build/main

clean:
	rm -f build/main