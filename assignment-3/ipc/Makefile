# _*_ Makefile _*_

all: p1-sockets.o utils.o
	gcc p1-sockets.o utils.o -o p1-sockets

p1-sockets.o: p1-sockets.c
	gcc -c p1-sockets.c -o p1-sockets.o

utils.o: utils.c
	gcc -c utils.c -o utils.o

clean:
	rm -f p1-sockets p1-sockets.o utils.o
