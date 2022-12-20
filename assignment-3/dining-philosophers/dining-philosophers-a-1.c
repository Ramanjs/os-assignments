#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int fork1 = 0, fork2 = 0, fork3 = 0, fork4 = 0, fork5 = 0;

void* eat1(void* args) {
  fork1 = 1;
  fork2 = 1;
  printf("Philosopher 1 started eating using fork1 and fork2\n");
  sleep(1);
  printf("Philosopher 1 finished eating using fork1 and fork2\n");
  fork1 = 0;
  fork2 = 0;
  return NULL;
}

void* eat2(void* args) {
  fork2 = 1;
  fork3 = 1;
  printf("Philosopher 2 started eating using fork2 and fork3\n");
  sleep(1);
  printf("Philosopher 2 finished eating using fork2 and fork3\n");
  fork2 = 0;
  fork3 = 0;
  return NULL;
}

void* eat3(void* args) {
  fork3 = 1;
  fork4 = 1;
  printf("Philosopher 3 started eating using fork3 and fork4\n");
  sleep(1);
  printf("Philosopher 3 finished eating using fork3 and fork4\n");
  fork2 = 0;
  fork3 = 0;
  return NULL;
}

void* eat4(void* args) {
  fork4 = 1;
  fork5 = 1;
  printf("Philosopher 4 started eating using fork4 and fork5\n");
  sleep(1);
  printf("Philosopher 4 finished eating using fork4 and fork5\n");
  fork4 = 0;
  fork5 = 0;
  return NULL;
}

void* eat5(void* args) {
  fork5 = 1;
  fork1 = 1;
  printf("Philosopher 5 started eating using fork5 and fork1\n");
  sleep(1);
  printf("Philosopher 5 finished eating using fork5 and fork1\n");
  fork5 = 0;
  fork1 = 0;
  return NULL;
}

int main(int argc, char *argv[]) {
  printf("Initialising table\n");
  pthread_t p1, p2, p3, p4, p5;

  pthread_create(&p1, NULL, &eat1, NULL);
  pthread_create(&p4, NULL, &eat4, NULL);
  pthread_join(p1, NULL);
  pthread_join(p4, NULL);

  pthread_create(&p2, NULL, &eat2, NULL);
  pthread_create(&p5, NULL, &eat5, NULL);
  pthread_join(p2, NULL);
  pthread_join(p5, NULL);

  pthread_create(&p3, NULL, &eat3, NULL);
  pthread_join(p3, NULL);
  return 0;
}
