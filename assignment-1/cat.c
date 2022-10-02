#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

void printContents(char *path) {
    char pwd[1000];
    getcwd(pwd, 1000);
    strcat(pwd, "/");
    strcat(pwd, path);
    FILE *ptr = fopen(pwd, "r");
    if (ptr == NULL) {
        char err[100];
        perror(err);
        printf("%s", err);
        return;
    }
    char ch;
    ch = fgetc(ptr);
    while (ch != EOF) {
        printf("%c", ch);
        ch = fgetc(ptr);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("too few arguments\n");
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        printContents(argv[i]);
    }
    printf("\n");
    return 0;
}
