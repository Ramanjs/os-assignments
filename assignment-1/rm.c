#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void removeFile(char *path) {
    char pwd[1000];
    getcwd(pwd, 1000);
    strcat(pwd, "/");
    strcat(pwd, path);
    if (unlink(pwd) == -1) {
        char err[100];
        perror(err);
        printf("%s", err);
    }
}

int main(int argc, char *argv[]) {
    //
    // Defile options
    char option1 = 'r';
    char option2 = 'f';
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

    for (int i = 1; i < argc; ++i) {
        removeFile(argv[i]);
    }
    return 0;
}
