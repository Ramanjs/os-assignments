## Assignment 2

### 1.1

`thread_sched.c` creates 3 threads, each with a different priority and scheduling policy. Is measures the difference in time taken to execute identical code but using different scheduling classes: SCHED_OTHER, SCHED_RR, and SCHED_FIFO. Policy and priority is set using the `pthread_setschedparam` syscall inside a thread function. 

There are 3 identical thread functions: countA(), countB(), countC(). All these functions count from 1 to 2^32 in a loop. `clock_gettime` syscall is used to calculate the time taken to execute a single `count` function. I have generated 10 values for each policy and stored them in a trace file. That data is then read by python script and displayed into a bar graph using the `plotly` plotting library.

### 1.2

The general idea is the same as the first problem. Here we are creating forks instead of processes and compiling a fresh copy of the linux kernel in that process using a bash script. The syscall used to set the priority and policies is `sched_setscheduler`. A separate bash script is run using the `exec` system call that compiles 3 different copies of the kernel. Data collectiona and plotting is done in the same way as above.

### 2

A buffer array is first used to copy the source array from user space to kernel space using the `__copy_from_user` syscall. Then the buffer is copied to the destination array using the `__copy_to_user` syscall. 

Copying a 2d array is similar to copying 1d array as the rows are arranged one after the other in memory. It means that we only need to copy (rows x columns) cells from the src to dest to effectively copy the whole 2d array.

The new syscall is added to the kernel syscall table `syscall_64.tbl` as syscall number 449. Also the new folder is added to the main Makefile. `2dcopy_test.c` tests the syscall using the `syscall` function and prints whether the syscall was successfull or not and if the src and dest arrays are equal.
