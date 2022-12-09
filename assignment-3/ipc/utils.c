#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "utils.h"

char** generateRandomStrings() {
  char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
  char** strings = malloc(STRING_ARRAY_LENGTH * sizeof(char*));
  for (int i = 0; i < STRING_ARRAY_LENGTH; i++) {
    strings[i] = malloc(STRING_LENGTH * sizeof(char));
    strings[i][0] = 0;
  }

  for (int i = 0; i < STRING_ARRAY_LENGTH; ++i) {
    for (int j = 0; j < STRING_LENGTH - 1; ++j) {
      int index = rand() % (int) (sizeof chars - 1);
      strings[i][j] = chars[index];
    }
    strings[i][STRING_LENGTH - 1] = 0;
  }

  return strings;
}

void printStrings(char** strings) {
  for (int i = 0; i < STRING_ARRAY_LENGTH; i++) {
    printf("%s\n", strings[i]);
  }
}

void checkError(int status) {
  if (status == -1) {
    printf("Encountered an error! : %s\n", strerror(errno));
    exit(1);
  }
}

char* getStringAt(char* arr, int n) {
  return arr + (n * STRING_LENGTH);
}

struct timespec getTimeDiff(struct timespec start, struct timespec finish) {
    struct timespec timeDiff;
    timeDiff.tv_sec = finish.tv_sec - start.tv_sec;
    timeDiff.tv_nsec = finish.tv_nsec - start.tv_nsec;

    if (timeDiff.tv_nsec < 0) {
        timeDiff.tv_nsec += 1000000000;
        timeDiff.tv_sec -= 1;
    }

    return timeDiff;
}
