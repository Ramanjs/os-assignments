#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "processinfo"
#define CLASS_NAME "proc"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A kernel module that reads the task_struct of a given process and prints information about it");
MODULE_VERSION("1.0");

static int majorNumber;
static struct class *procClass = NULL;
static struct device *procDevice = NULL;
static struct cdev procCdev;
long current_pid;

static int device_open(struct inode *inode, struct file *file) {
  return 0;
}

static int device_release(struct inode *inode, struct file *file) {
  return 0;
}

static ssize_t device_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos) {
  // This function is called when the device is read from
  // You can read the information you want to return to the user space program here

  // First, you will need to find the task_struct for the given PID
  // The PID was passed to the kernel module by the user space program in the device_write function
  struct task_struct *task;
  rcu_read_lock();
  // rcu_read_lock() is a function that acquires a read lock on the RCU (Read-Copy Update) data structure
  // This is necessary to ensure that the task_struct you are reading is not being modified by another kernel function
  task = find_task_by_vpid(current_pid);
  // find_task_by_vpid() is a function that returns the task_struct for the given PID
  // It returns NULL if the task is not found
  if (!task) {
    rcu_read_unlock();
    // rcu_read_unlock() releases the read lock acquired by rcu_read_lock()
    return -EINVAL;
  }

  // Now that you have the task_struct, you can read the values of the fields you are interested in
  pid_t task_pid = task->pid;
  uid_t task_uid = task->cred->uid;
  pid_t task_pgid = task->cred->gid;
  char *task_comm = task->comm;

  // You can now format the information you want to return to the user space program as a string
  char info[256];
  sprintf(info, "PID: %d\nUID: %d\nPGID: %d\nCommand: %s\n", task_pid, task_uid, task_pgid, task_comm);

  // Finally, you can copy the string to the user space program's buffer using the copy_to_user() function
  if (copy_to_user(buf, info, strlen(info)) != 0) {
    rcu_read_unlock();
    return -EFAULT;
  }

  // Don't forget to release the read lock and return the number of bytes copied to the user space program's buffer
  rcu_read_unlock();
  return strlen(info);
}

static ssize_t device_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos) {
  // This function is called when the device is written to
  // You can use this function to pass the PID of the process whose task_struct you want to read
  // to the kernel module

  // First, you will need to parse the PID from the user space program's input
  long pid;
  if (kstrtol_from_user(buf, count, 10, &pid) < 0) {
    // kstrtol_from_user() is a function that converts a string from user space to a long integer
    // It returns 0 on success and a negative value on error
    // You can use this function to parse the PID from the user space program's input
    return -EINVAL;
  }

  // The PID has been successfully parsed
  // You can now store it in a global variable or in a module parameter to be used by the device_read function later
  // In this example, we will use a global variable
  current_pid = pid;

  return count;
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

  printk(KERN_INFO "Successfully initialized the device\n");
  return 0;
}

static void __exit proc_exit(void) {
  // Clean up the device when the module is unloaded
  cdev_del(&procCdev);
  device_destroy(procClass, dev_num);
  class_destroy(procClass);
  unregister_chrdev_region(dev_num, 1);
  printk(KERN_INFO "Successfully unloaded the device\n");
}

module_init(proc_init);
module_exit(proc_exit);
