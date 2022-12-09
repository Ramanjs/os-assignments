#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <asm-generic/errno-base.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/mman.h>
#include "utils.h"

int main(int argc, char *argv[]) {
  char** strings = generateRandomStrings();

  int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0777);
  if (errno != EEXIST) checkError(fd);
  sem_t* p1Sem = sem_open(SEM_P1, O_CREAT, 0777, 1);
  sem_t* p2Sem = sem_open(SEM_P2, O_CREAT, 0777, 0);

  ftruncate(fd, SHM_SIZE);
  char* data = (char*) mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  int index = 1;
  char buf[STRING_LENGTH];
  for (int i = 1; i <= STRING_ARRAY_LENGTH / 5; ++i) {
    sem_wait(p1Sem);
    for (int j = 0; j < 10; j += 2) {
      snprintf(buf, STRING_LENGTH, "%d", index);
      strncpy(getStringAt(data, j), buf, STRING_LENGTH);
      strncpy(getStringAt(data, j + 1), strings[index - 1], STRING_LENGTH);
      index++;
    }
    sem_post(p2Sem);

    sem_wait(p1Sem);
    strncpy(buf, getStringAt(data, 0), STRING_LENGTH);
    printf("Index of last element: %s\n", buf);
    sem_post(p1Sem);
  }

  munmap(data, SHM_SIZE);
  close(fd);

  sem_close(p1Sem);
  sem_close(p2Sem);
  /*sem_unlink(SEM_NAME);*/

  return 0;
}
