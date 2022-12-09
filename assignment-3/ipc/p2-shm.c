#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/mman.h>
#include "utils.h"

int main(int argc, char *argv[]) {
  char buf[STRING_LENGTH];

  int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0777);
  if (errno != EEXIST) checkError(fd);
  sem_t* p1Sem = sem_open(SEM_P1, O_CREAT, 0777, 1);
  sem_t* p2Sem = sem_open(SEM_P2, O_CREAT, 0777, 0);

  ftruncate(fd, SHM_SIZE);
  char* data = (char*) mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  for (int i = 1; i <= STRING_ARRAY_LENGTH / 5; ++i) {
    sem_wait(p2Sem);
    for (int j = 0; j < 10; j += 2) {
      printf("%s: %s\n", getStringAt(data, j), getStringAt(data, j + 1));
    }
    strncpy(getStringAt(data, 0), getStringAt(data, 8), STRING_LENGTH);
    sem_post(p1Sem);

  }

  munmap(data, SHM_SIZE);
  close(fd);

  sem_close(p1Sem);
  sem_close(p2Sem);
  /*sem_unlink(SEM_NAME);*/

  return 0;
}
