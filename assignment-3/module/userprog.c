#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s PID\n", argv[0]);
    return 1;
  }

  // Open the character device file
  int fd = open("/dev/processinfo", O_RDWR);
  if (fd < 0) {
    perror("Failed to open the device");
    return 1;
  }

  // Convert the PID from the command line argument to a string
  char pid_str[16];
  sprintf(pid_str, "%d", atoi(argv[1]));

  // Write the PID to the character device file
  if (write(fd, pid_str, strlen(pid_str)) < 0) {
    perror("Failed to write to the device");
    return 1;
  }

  // Read the information about the process from the character device file
  char info[256];
  if (read(fd, info, sizeof(info)) < 0) {
    perror("Failed to read from the device");
    return 1;
  }

  // Print the information
  printf("%s", info);

  // Close the character device file
  close(fd);

  return 0;
}

