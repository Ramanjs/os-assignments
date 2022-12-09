#include <bits/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <unistd.h>
#include "utils.h"

int main(int argc, char *argv[]) {
  struct timespec start, finish, timeDiff;
  char** strings = generateRandomStrings();
  /*printStrings(strings);*/

  int status;
  int numWritten, numRead;

  struct sockaddr_un addr;
  int sfd;
  sfd = socket(AF_UNIX, SOCK_STREAM, 0); checkError(sfd);

  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);

  status = connect(sfd, (struct sockaddr*) &addr, sizeof(struct sockaddr_un));

  char index[STRING_LENGTH] = {0};

  clock_gettime(CLOCK_REALTIME, &start);
  for (int i = 1; i <= STRING_ARRAY_LENGTH; i++) {
    numWritten = write(sfd, strings[i - 1], STRING_LENGTH);
    if (numWritten != STRING_LENGTH) checkError(-1);

    snprintf(index, sizeof(i), "%d", i);
    write(sfd, index, STRING_LENGTH);

    if (i % STRING_LENGTH == 0) {
      numRead = read(sfd, index, STRING_LENGTH);
      printf("Index of last element: %s\n", index);
    }
  }
  clock_gettime(CLOCK_REALTIME, &finish);

  timeDiff = getTimeDiff(start, finish);
  printf("Time taken: %d.%.5lds\n", (int) timeDiff.tv_sec, timeDiff.tv_nsec);

  return 0;
}
