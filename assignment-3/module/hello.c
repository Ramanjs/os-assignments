#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/pid.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/uidgid.h>

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Raman");
MODULE_DESCRIPTION("A simple module to get process info from its task_struct");

struct task_struct* task;
struct pid* pid_s;
static int pid = 0;

module_param(pid, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(pid, "Process ID");

static int __init hello_init(void) {
	pid_s = find_get_pid(pid);
	task = get_pid_task(pid_s, PIDTYPE_PID);
	printk(KERN_INFO "Task pid: %d", task->pid);
	printk(KERN_INFO "Task user id: %d", (task->cred->uid).val);
	printk(KERN_INFO "Task group id: %d", (task->cred->gid).val);
	printk(KERN_INFO "Task command name: %s", task->comm);
	printk(KERN_INFO "Executed module successfully");
	return 0;
}

static void __exit hello_cleanup(void) {
	printk(KERN_INFO "Cleaning up module.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);
