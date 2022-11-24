## Assignment 2

### 1.1

`thread_sched.c` creates 3 threads, each with a different priority and scheduling policy. Is measures the difference in time taken to execute identical code but using different scheduling classes: SCHED_OTHER, SCHED_RR, and SCHED_FIFO. Policy and priority is set using the `pthread_setschedparam` syscall inside a thread function. 

There are 3 identical thread functions: countA(), countB(), countC(). All these functions count from 1 to 2^32 in a loop. `clock_gettime` syscall is used to calculate the time taken to execute a single `count` function. I have generated 10 values for each policy and stored them in a trace file. That data is then read by python script and displayed into a bar graph using the `plotly` plotting library.

### 1.2

The general idea is the same as the first problem. Here we are creating forks instead of processes and compiling a fresh copy of the linux kernel in that process using a bash script. The syscall used to set the priority and policies is `sched_setscheduler`. A separate bash script is run using the `exec` system call that compiles 3 different copies of the kernel. Data collectiona and plotting is done in the same way as above.
