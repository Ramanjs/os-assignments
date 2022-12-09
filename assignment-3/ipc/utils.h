#include <bits/types/struct_timespec.h>
#include <time.h>
#define SOCK_PATH "/tmp/p1-socket"
#define P1_FIFO_PATH "/tmp/p1-fifo"
#define P2_FIFO_PATH "/tmp/p2-fifo"
#define STRING_ARRAY_LENGTH 50
#define STRING_LENGTH 5
#define SHM_NAME "os-a3"
#define SHM_SIZE sizeof(char*) * STRING_LENGTH * 5 * 2
#define SEM_P1 "os-a3-p1"
#define SEM_P2 "os-a3-p2"
char** generateRandomStrings();
void printStrings(char**);
void checkError(int);
char* getStringAt(char*, int);
struct timespec getTimeDiff(struct timespec, struct timespec);
