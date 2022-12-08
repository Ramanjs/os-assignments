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
  char index[STRING_LENGTH];
  for (int i = 1; i <= STRING_ARRAY_LENGTH; i++) {
    numRead = read(cfd, string, STRING_LENGTH);
    if (numRead != STRING_LENGTH) checkError(numRead);

    numRead = read(cfd, index, STRING_LENGTH);
    if (numRead != STRING_LENGTH) checkError(numRead);

    printf("%s: %s\n", index, string);

    if (i % STRING_LENGTH == 0) {
      char buf[STRING_LENGTH] = {0};
      snprintf(buf, sizeof(i), "%d", i);
      write(cfd, buf, STRING_LENGTH);
    }
  }
  return 0;
}
