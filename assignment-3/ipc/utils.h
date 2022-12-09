#define SOCK_PATH "/tmp/p1-socket"
#define P1_FIFO_PATH "/tmp/p1-fifo"
#define P2_FIFO_PATH "/tmp/p2-fifo"
#define STRING_ARRAY_LENGTH 50
#define STRING_LENGTH 5
char** generateRandomStrings();
void printStrings(char**);
void checkError(int);
