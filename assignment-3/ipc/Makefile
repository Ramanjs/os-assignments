# _*_ Makefile _*_

all: fifos sockets shms

shms: p1-shm.o p2-shm.o utils.o
	gcc -g p1-shm.o utils.o -o p1-shm
	gcc -g p2-shm.o utils.o -o p2-shm

fifos: p1-fifo.o p2-fifo.o utils.o
	gcc -g p1-fifo.o utils.o -o p1-fifo
	gcc -g p2-fifo.o utils.o -o p2-fifo

sockets: p1-sockets.o p2-sockets.o utils.o
	gcc -g p1-sockets.o utils.o -o p1-sockets
	gcc -g p2-sockets.o utils.o -o p2-sockets

p1-sockets.o: p1-sockets.c
	gcc -g -c p1-sockets.c -o p1-sockets.o

p2-sockets.o: p2-sockets.c
	gcc -g -c p2-sockets.c -o p2-sockets.o

p1-fifo.o: p1-fifo.c
	gcc -g -c p1-fifo.c -o p1-fifo.o

p2-fifo.o: p2-fifo.c
	gcc -g -c p2-fifo.c -o p2-fifo.o

p1-shm.o: p1-shm.c
	gcc -g -c p1-shm.c -o p1-shm.o

p2-shm.o: p2-shm.c
	gcc -g -c p2-shm.c -o p2-shm.o

utils.o: utils.c
	gcc -c utils.c -o utils.o

clean:
	rm -f p1-sockets p1-sockets.o p2-sockets p2-sockets.o
	rm -f p1-fifo p1-fifo.o p2-fifo p2-fifo.o
	rm -f p1-shm p1-shm.o p2-shm p2-shm.o
	rm -f utils.o
