CC = gcc
INCLUDES = -I./include
SRCS = main.c src/server.c


all: build/main

build/main: $(SRCS)
	$(CC) $(INCLUDES) $(SRCS) -o build/main

%.o: %.c
	$(CC) -I./include -c $< -o $@

clean:
	rm -f build/main