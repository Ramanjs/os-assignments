#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "utils.h"

int main(int argc, char *argv[]) {
  struct sockaddr_un addr;
  int sfd, cfd;
  int status;

  sfd = socket(AF_UNIX, SOCK_STREAM, 0); checkError(sfd);

  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);

  status = bind(sfd, (struct sockaddr*) &addr, sizeof(struct sockaddr_un));

  status = listen(sfd, 1); checkError(status);

  cfd = accept(sfd, NULL, NULL); checkError(cfd);

  int numRead;
  char string[STRING_LENGTH];
  while ((numRead = read(cfd, string, STRING_LENGTH)) > 0) {
    checkError(numRead);
    printf("%s\n", string);
  }
  return 0;
}
