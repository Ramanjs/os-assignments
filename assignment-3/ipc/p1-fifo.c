#include <bits/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <asm-generic/errno-base.h>
#include "utils.h"

int main(int argc, char *argv[]) {
  struct timespec start, finish, timeDiff;
  char** strings = generateRandomStrings();

  int status;
  int numRead, numWritten;
  char buf[STRING_LENGTH];

  status = mkfifo(P1_FIFO_PATH, S_IRUSR | S_IWUSR | S_IWGRP);
  if (errno != EEXIST) checkError(status);

  int fifoWrite = open(P1_FIFO_PATH, O_WRONLY); checkError(fifoWrite);
  int fifoRead = open(P2_FIFO_PATH, O_RDONLY); checkError(fifoRead);

  clock_gettime(CLOCK_REALTIME, &start);
  for (int i = 1; i <= STRING_ARRAY_LENGTH; i++) {
    numWritten = write(fifoWrite, strings[i - 1], STRING_LENGTH);

    if (numWritten != STRING_LENGTH) checkError(-1);

    if (i % 5 == 0) {
      numRead = read(fifoRead, buf, STRING_LENGTH);
      if (numRead != STRING_LENGTH) checkError(-1);

      printf("Index of last element: %s\n", buf);
    }
  }
  clock_gettime(CLOCK_REALTIME, &finish);

  timeDiff = getTimeDiff(start, finish);
  printf("Time taken: %d.%.5lds\n", (int) timeDiff.tv_sec, timeDiff.tv_nsec);

  return 0;
}
