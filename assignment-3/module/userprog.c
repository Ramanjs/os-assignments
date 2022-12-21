#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void checkError(int status) {
  if (status < 0) {
    printf("Encountered an error! : %s\n", strerror(errno));
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  int fd = open("/dev/processinfo", O_RDWR); checkError(fd);

  char pidString[16];
  sprintf(pidString, "%d", atoi(argv[1]));

  int status;
  status = write(fd, pidString, strlen(pidString)); checkError(status);

  char processInfo[256];
  status = read(fd, processInfo, sizeof(processInfo)); checkError(status);

  printf("%s", processInfo);

  close(fd);
  return 0;
}

