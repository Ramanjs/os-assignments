# IPC Mechanisms

I've used different ipc mechanisms to solve the given problem: sockets, fifos and shared memory.

## Sockets

* The server first setups a socket that listens for incoming connections. The client program then connects to the the server and writes 5 random strings at a time. On receiving the strings, the server acknowledges the data by sending back the ID of the latest received string.

## Fifos

* Both programs use two fifos. One to read and the other one to write to the other process. The flow is the same as the above sockets implementation, except fifos are blocking if the other end is not reading/writing at the same time. So no synchronisation primitives are required here.

## Shared Memory

* Shared memory is not blocking by nature. To implement the same process with, I've used 2 semaphores to synchronise the read/write process: SEM_P1 and SEM_P2. SEM_P1 is initialised with a value of 1 while SEM_P2 with 0. p1-shm.c opens a shm and acquires SEM_P1 before writing to it and then increases the value of SEM_P2. Now p2-shm.c can acquire SEM_P2 and read from the shared memory. After it is done reading, p2 increases the value of SEM_P1 so p1 knows it can read the acknowledgement from p2. This way both processes synchronise their communication using shared memory.
