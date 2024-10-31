CC = gcc

main: main.c
	$(CC) main.c -o build/main

clean:
	rm -f build/main