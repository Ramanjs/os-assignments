# Syscall as a Kernel Module

There are 3 approaches to this problem. First it to make a module that takes in the pid as an argument and logs the process details in the kernel log. Second approach overrides the kernel's sys_call_table to set its pointer to a function inside the kernel module. Third approach, which I have implemented is to write a device driver that registers a fake character device with the kernel so that a user space program can read and write data from/to it.

## Simple Kernel Module
A simple kernel module that uses the module_param macro to take in input while its being inserted into the kernel using the insmod command. The program then uses the find_get_pid function to read the process's task_struct and log the details to the kernel log.

## Char Device Driver
Registers a fake device with the kernel and registers its read and write function using the fops struct. The process to read/write the task_struct is the same except this returns the process info as a string to the user-space program. Errors are handled if the device fails to register at any point during the module loading.
