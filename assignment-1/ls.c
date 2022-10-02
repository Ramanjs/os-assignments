#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char *path = malloc(1000 * sizeof(char));
    if (argc == 1) {
        path = getcwd(path, 1000);
    } else {
        path = argv[1];
    }
    DIR *dir = opendir(path);
    struct dirent *currentEntry = readdir(dir);

    while (currentEntry != NULL) {
        if (currentEntry->d_name[0] != '.') printf("%s  ", currentEntry->d_name);
        currentEntry = readdir(dir);
    }
    printf("\n");
    return 0;
}
