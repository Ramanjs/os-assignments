#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

sem_t fork1, fork2, fork3, fork4, fork5;

void checkError(int status) {
  if (status != 0) {
    printf("Encountered an error! :%s\n", strerror(errno));
    exit(1);
  }
}

void* eat1(void* args) {
  int st = 0;
  st = sem_wait(&fork1); checkError(st);
  st = sem_wait(&fork2); checkError(st);
  printf("Philosopher 1 started eating using fork1 and fork2\n");
  printf("Philosopher 1 finished eating using fork1 and fork2\n");
  st = sem_post(&fork2); checkError(st);
  st = sem_post(&fork1); checkError(st);

  return NULL;
}

void* eat2(void* args) {
  int st = 0;
  st = sem_wait(&fork2); checkError(st);
  st = sem_wait(&fork3); checkError(st);
  printf("Philosopher 2 started eating using fork2 and fork3\n");
  printf("Philosopher 2 finished eating using fork2 and fork3\n");
  st = sem_post(&fork3); checkError(st);
  st = sem_post(&fork2); checkError(st);

  return NULL;
}

void* eat3(void* args) {
  int st = 0;
  st = sem_wait(&fork3); checkError(st);
  st = sem_wait(&fork4); checkError(st);
  printf("Philosopher 3 started eating using fork3 and fork4\n");
  printf("Philosopher 3 finished eating using fork3 and fork4\n");
  st = sem_post(&fork4); checkError(st);
  st = sem_post(&fork3); checkError(st);

  return NULL;
}

void* eat4(void* args) {
  int st = 0;
  st = sem_wait(&fork4); checkError(st);
  st = sem_wait(&fork5); checkError(st);
  printf("Philosopher 4 started eating using fork4 and fork5\n");
  printf("Philosopher 4 finished eating using fork4 and fork5\n");
  st = sem_post(&fork5); checkError(st);
  st = sem_post(&fork4); checkError(st);

  return NULL;
}

void* eat5(void* args) {
  int st = 0;
  st = sem_wait(&fork5); checkError(st);
  st = sem_wait(&fork1); checkError(st);
  printf("Philosopher 5 started eating using fork5 and fork1\n");
  printf("Philosopher 5 finished eating using fork5 and fork1\n");
  st = sem_post(&fork1); checkError(st);
  st = sem_post(&fork5); checkError(st);

  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t p1, p2, p3, p4, p5;

  int st = 0;

  st = sem_init(&fork1, 0, 1); checkError(st);
  st = sem_init(&fork2, 0, 1); checkError(st);
  st = sem_init(&fork3, 0, 1); checkError(st);
  st = sem_init(&fork4, 0, 1); checkError(st);
  st = sem_init(&fork5, 0, 1); checkError(st);

  pthread_create(&p1, NULL, &eat1, NULL);
  pthread_create(&p2, NULL, &eat2, NULL);
  pthread_create(&p3, NULL, &eat3, NULL);
  pthread_create(&p4, NULL, &eat4, NULL);
  pthread_create(&p5, NULL, &eat5, NULL);

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  pthread_join(p3, NULL);
  pthread_join(p4, NULL);
  pthread_join(p5, NULL);
  return 0;
}
