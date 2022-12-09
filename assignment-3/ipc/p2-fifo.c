#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <asm-generic/errno-base.h>
#include "utils.h"

int main(int argc, char *argv[]) {

  int status;
  int numRead, numWritten;
  char buf[STRING_LENGTH];

  status = mkfifo(P2_FIFO_PATH, S_IRUSR | S_IWUSR | S_IWGRP);
  if (errno != EEXIST) checkError(status);

  int fifoRead = open(P1_FIFO_PATH, O_RDONLY); checkError(fifoRead);
  int fifoWrite = open(P2_FIFO_PATH, O_WRONLY); checkError(fifoWrite);

  for (int i = 1; i <= STRING_ARRAY_LENGTH; i++) {
    numRead = read(fifoRead, buf, STRING_LENGTH);
    if (numRead != STRING_LENGTH) checkError(-1);

    printf("%s\n", buf);

    if (i % 5 == 0) {
      snprintf(buf, STRING_LENGTH, "%d", i);
      numWritten = write(fifoWrite, buf, STRING_LENGTH);
      if (numWritten != STRING_LENGTH) checkError(-1);
    }
  }

  return 0;
}
