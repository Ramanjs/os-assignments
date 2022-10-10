#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

void printContents(char *path, int setOption1, int setOption2) {
    int lineNumber = 1;

    char pwd[1000];
    getcwd(pwd, 1000);
    strcat(pwd, "/");
    strcat(pwd, path);

    FILE *ptr = fopen(pwd, "r");
    if (ptr == NULL) {
        printf("%s", strerror(errno));
        return;
    }
    char ch;
    ch = fgetc(ptr);
    printf("%5d  ", lineNumber++);
    while (ch != EOF) {
        if (setOption1 && ch == '\n') printf("$");
        printf("%c", ch);
        char chCopy = ch;
        ch = fgetc(ptr);
        if (setOption2 && chCopy == '\n' && ch != EOF) printf("%5d  ", lineNumber++);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("too few arguments\n");
        return 0;
    }

    // Define options
    char option1 = 'E';
    char option2 = 'n';
    int setOption1 = 0;
    int setOption2 = 0;

    // Define files array
    char **files = malloc(10 * sizeof(char*));
    for (int i = 0; i < 10; ++i) {
        files[i] = malloc(100 * sizeof(char));
        files[i][0] = '\0';
    }
    int numFiles = 0;


    // Extract arguments and options
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 0; j < strlen(argv[i]); j++) {
                if (argv[i][j] == option1) setOption1 = 1;
                if (argv[i][j] == option2) setOption2 = 1;
            }
        } else {
            strcat(files[numFiles], argv[i]);
            numFiles++;
        }
    }

    for (int i = 0; i < numFiles; ++i) {
        printContents(files[i], setOption1, setOption2);
    }
    printf("\n");
    return 0;
}
