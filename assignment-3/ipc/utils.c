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
