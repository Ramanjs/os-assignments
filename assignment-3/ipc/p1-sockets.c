#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "utils.h"

int main(int argc, char *argv[]) {
  char** strings = generateRandomStrings();
  printStrings(strings);

  int status;

  struct sockaddr_un addr;
  int sfd;
  sfd = socket(AF_UNIX, SOCK_STREAM, 0); checkError(sfd);

  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);

  status = connect(sfd, (struct sockaddr*) &addr, sizeof(struct sockaddr_un));

  for (int i = 0; i < STRING_ARRAY_LENGTH; i++) {
    int numWritten = write(sfd, strings[i], STRING_LENGTH);
    if (numWritten != STRING_LENGTH) checkError(-1);

  }
  return 0;
}
