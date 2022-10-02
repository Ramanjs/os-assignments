#include <stdio.h>
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
    for (int i = 1; i < argc; ++i) {
        removeFile(argv[i]);
    }
    return 0;
}
