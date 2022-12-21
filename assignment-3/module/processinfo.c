#include <linux/init.h>
#include <linux/module.h>
#include <linux/pid.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/kernel.h>

#define DEVICE_NAME "processinfo"
#define CLASS_NAME "proc"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ramanjeet Singh");
MODULE_DESCRIPTION("A kernel module that takes in a process ID, finds the task_struct of the given process and prints information about it using the task_struct");

static int majorNumber;
static struct class *procClass = NULL;
static struct device *procDevice = NULL;
static struct cdev procCdev;
static long current_pid;
static int dev_num;

static ssize_t device_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos) {
  struct task_struct *task;
  rcu_read_lock();
  task = get_pid_task(find_get_pid(current_pid), PIDTYPE_PID);
  if (!task) {
    rcu_read_unlock();
    return -EINVAL;
  }

  int pid = task->pid;
  int uid = (task->cred->uid).val;
  int pgid = (task->cred->gid).val;
  char *comm = task->comm;

  char processInfo[256];
  sprintf(processInfo, "PID: %d\nUID: %d\nPGID: %d\nCommand: %s\n", pid, uid, pgid, comm);

  if (copy_to_user(buf, processInfo, strlen(processInfo)) != 0) {
    rcu_read_unlock();
    return -EFAULT;
  }

  rcu_read_unlock();
  return strlen(processInfo);
}

static ssize_t device_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos) {
  long pid;
  if (kstrtol_from_user(buf, count, 10, &pid) < 0) {
    return -EINVAL;
  }

  current_pid = pid;
  return count;
}

static int device_open(struct inode *inode, struct file *file) {
  return 0;
}

static int device_release(struct inode *inode, struct file *file) {
  return 0;
}

static struct file_operations fops = {
  .open = device_open,
  .release = device_release,
  .read = device_read,
  .write = device_write,
};

static int __init proc_init(void) {
  if (alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME) < 0) {
    printk(KERN_ERR "Failed to allocate a major number for the device\n");
    return -1;
  }
  majorNumber = MAJOR(dev_num);

  procClass = class_create(THIS_MODULE, CLASS_NAME);
  if (IS_ERR(procClass)) {
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_ERR "Failed to create the device class\n");
    return PTR_ERR(procClass);
  }

  procDevice = device_create(procClass, NULL, dev_num, NULL, DEVICE_NAME);
  if (IS_ERR(procDevice)) {
    class_destroy(procClass);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_ERR "Failed to create the device\n");
    return PTR_ERR(procDevice);
  }

  cdev_init(&procCdev, &fops);
  procCdev.owner = THIS_MODULE;
  if (cdev_add(&procCdev, dev_num, 1) < 0) {
    device_destroy(procClass, dev_num);
    class_destroy(procClass);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_ERR "Failed to add the character device\n");
    return -1;
  }

  printk(KERN_INFO "Successfully loaded the device\n");
  return 0;
}

static void __exit proc_exit(void) {
  cdev_del(&procCdev);
  device_destroy(procClass, dev_num);
  class_destroy(procClass);
  unregister_chrdev_region(dev_num, 1);
  printk(KERN_INFO "Successfully unloaded the device\n");
}

module_init(proc_init);
module_exit(proc_exit);
