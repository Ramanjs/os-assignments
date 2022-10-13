#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

#include "utils.h"

void removeFile(char *path, int setOption2) {
    if (unlink(path) == -1) {
        if (!(setOption2 && errno == ENOENT)) printf("%s\n", strerror(errno));
    }
}

void removeIt(char *filePath, int setOption2) {
    if (isDir(filePath)) {
        DIR *dir = opendir(filePath);
        struct dirent *currentEntry = readdir(dir);
        while (currentEntry != NULL) {
            if (strcmp(currentEntry->d_name, ".") == 0 || strcmp(currentEntry->d_name, "..") == 0) {
                currentEntry = readdir(dir);
                continue;
            }
            char path[1000];
            strcpy(path, filePath);
            strcat(path, "/");
            strcat(path, currentEntry->d_name);
            removeIt(path, setOption2);
            currentEntry = readdir(dir);
        }
        rmdir(filePath);
        closedir(dir);
    } else {
        removeFile(filePath, setOption2);
    }
}

int main(int argc, char *argv[]) {
    char* path;

    // Defile options
    char option1 = 'r';
    char option2 = 'f';
    int setOption1 = 0;
    int setOption2 = 0;

    // Define files array
    char **files = getFilesArray();
    int numFiles = 0;

    // Extract arguments and options
    extractArguments(files, argv, argc, option1, option2, &setOption1, &setOption2, &numFiles);


    for (int i = 0; i < numFiles; ++i) {
        path = getenv("PWD");
        strcat(path, "/");
        strcat(path, files[i]);

        if (setOption1) removeIt(path, setOption2);
        else removeFile(path, setOption2);
    }
    return 0;
}
