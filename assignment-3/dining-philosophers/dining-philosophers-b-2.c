#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <unistd.h>

sem_t fork1, fork2, fork3, fork4, fork5;
sem_t bowl1, bowl2;

void checkError(int status) {
  if (status != 0) {
    printf("Encountered an error! :%s\n", strerror(errno));
    exit(1);
  }
}

void* eat1(void* args) {
  printf("Philosopher 1 is thinking\n");
  int st = 0;
  st = sem_wait(&fork1); checkError(st);
  st = sem_wait(&fork2); checkError(st);
  int bowlval1, bowlval2, bowlChosen;
  while (1) {
    sem_getvalue(&bowl1, &bowlval1);
    sem_getvalue(&bowl2, &bowlval2);
    if (bowlval1 == 1) {
      sem_wait(&bowl1);
      bowlChosen = 1;
      break;
    }
    if (bowlval2 == 1) {
      sem_wait(&bowl2);
      bowlChosen = 2;
      break;
    }
  }
  printf("Philosopher 1 started eating using fork1 and fork2\n");
  printf("Philosopher 1 started eating using bowl %d\n", bowlChosen);
  sleep(1);
  printf("Philosopher 1 finished eating using bowl %d\n", bowlChosen);
  printf("Philosopher 1 finished eating using fork1 and fork2\n");
  if (bowlval1 == 1) {
    sem_post(&bowl1);
  }
  if (bowlval2 == 1) {
    sem_post(&bowl2);
  }
 
  st = sem_post(&fork2); checkError(st);
  st = sem_post(&fork1); checkError(st);

  return NULL;
}

void* eat2(void* args) {
  printf("Philosopher 2 is thinking\n");
  int st = 0;
  st = sem_wait(&fork2); checkError(st);
  st = sem_wait(&fork3); checkError(st);
  int bowlval1, bowlval2, bowlChosen;
  while (1) {
    sem_getvalue(&bowl1, &bowlval1);
    sem_getvalue(&bowl2, &bowlval2);
    if (bowlval1 == 1) {
      sem_wait(&bowl1);
      bowlChosen = 1;
      break;
    }
    if (bowlval2 == 1) {
      sem_wait(&bowl2);
      bowlChosen = 2;
      break;
    }
  }
  printf("Philosopher 2 started eating using fork2 and fork3\n");
  printf("Philosopher 2 started eating using bowl %d\n", bowlChosen);
  sleep(1);
  printf("Philosopher 2 finished eating using bowl %d\n", bowlChosen);
  printf("Philosopher 2 finished eating using fork2 and fork3\n");
  if (bowlval1 == 1) {
    sem_post(&bowl1);
  }
  if (bowlval2 == 1) {
    sem_post(&bowl2);
  }
 
  st = sem_post(&fork3); checkError(st);
  st = sem_post(&fork2); checkError(st);

  return NULL;
}

void* eat3(void* args) {
  printf("Philosopher 3 is thinking\n");
  int st = 0;
  st = sem_wait(&fork3); checkError(st);
  st = sem_wait(&fork4); checkError(st);
  int bowlval1, bowlval2, bowlChosen;
  while (1) {
    sem_getvalue(&bowl1, &bowlval1);
    sem_getvalue(&bowl2, &bowlval2);
    if (bowlval1 == 1) {
      sem_wait(&bowl1);
      bowlChosen = 1;
      break;
    }
    if (bowlval2 == 1) {
      sem_wait(&bowl2);
      bowlChosen = 2;
      break;
    }
  }
  printf("Philosopher 3 started eating using fork3 and fork4\n");
  printf("Philosopher 3 started eating using bowl %d\n", bowlChosen);
  sleep(1);
  printf("Philosopher 3 finished eating using bowl %d\n", bowlChosen);
  printf("Philosopher 3 finished eating using fork3 and fork4\n");
  if (bowlval1 == 1) {
    sem_post(&bowl1);
  }
  if (bowlval2 == 1) {
    sem_post(&bowl2);
  }
 
  st = sem_post(&fork4); checkError(st);
  st = sem_post(&fork3); checkError(st);

  return NULL;
}

void* eat4(void* args) {
  printf("Philosopher 4 is thinking\n");
  int st = 0;
  st = sem_wait(&fork4); checkError(st);
  st = sem_wait(&fork5); checkError(st);
  int bowlval1, bowlval2, bowlChosen;
  while (1) {
    sem_getvalue(&bowl1, &bowlval1);
    sem_getvalue(&bowl2, &bowlval2);
    if (bowlval1 == 1) {
      sem_wait(&bowl1);
      bowlChosen = 1;
      break;
    }
    if (bowlval2 == 1) {
      sem_wait(&bowl2);
      bowlChosen = 2;
      break;
    }
  }
  printf("Philosopher 4 started eating using fork4 and fork5\n");
  printf("Philosopher 4 started eating using bowl %d\n", bowlChosen);
  sleep(1);
  printf("Philosopher 4 finished eating using bowl %d\n", bowlChosen);
  printf("Philosopher 4 finished eating using fork4 and fork5\n");
  if (bowlval1 == 1) {
    sem_post(&bowl1);
  }
  if (bowlval2 == 1) {
    sem_post(&bowl2);
  }
 
  st = sem_post(&fork5); checkError(st);
  st = sem_post(&fork4); checkError(st);

  return NULL;
}

void* eat5(void* args) {
  printf("Philosopher 5 is thinking\n");
  int st = 0;
  st = sem_wait(&fork1); checkError(st);
  st = sem_wait(&fork5); checkError(st);
  int bowlval1, bowlval2, bowlChosen;
  while (1) {
    sem_getvalue(&bowl1, &bowlval1);
    sem_getvalue(&bowl2, &bowlval2);
    if (bowlval1 == 1) {
      sem_wait(&bowl1);
      bowlChosen = 1;
      break;
    }
    if (bowlval2 == 1) {
      sem_wait(&bowl2);
      bowlChosen = 2;
      break;
    }
  }
  printf("Philosopher 5 started eating using fork5 and fork1\n");
  printf("Philosopher 5 started eating using bowl %d\n", bowlChosen);
  sleep(1);
  printf("Philosopher 5 finished eating using bowl %d\n", bowlChosen);
  printf("Philosopher 5 finished eating using fork5 and fork1\n");
  if (bowlval1 == 1) {
    sem_post(&bowl1);
  }
  if (bowlval2 == 1) {
    sem_post(&bowl2);
  }
  st = sem_post(&fork5); checkError(st);
  st = sem_post(&fork1); checkError(st);

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
  st = sem_init(&bowl1, 0, 1); checkError(st);
  st = sem_init(&bowl2, 0, 1); checkError(st);

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
