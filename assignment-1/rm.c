#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

int isDir(char *path) {
    struct stat attrib;
    stat(path, &attrib);
    return S_ISDIR(attrib.st_mode);
}

void removeFile(char *path, int setOption2) {
    char filePath[1000];
    getcwd(filePath, 1000);
    strcat(filePath, "/");
    strcat(filePath, path);
    if (unlink(filePath) == -1) {
        if (!(setOption2 && errno == ENOENT)) printf("%s", strerror(errno));
    }
}

void removeIt(char *file, int setOption2) {
    if (isDir(file)) {
        DIR *dir = opendir(file);
        struct dirent *currentEntry = readdir(dir);
        while (currentEntry != NULL) {
            removeIt(currentEntry->d_name, setOption2);
            currentEntry = readdir(dir);
        }
    } else {
        removeFile(file, setOption2);
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

    for (int i = 0; i < numFiles; ++i) {
        if (setOption1) removeIt(files[i], setOption2);
        else removeFile(files[i], setOption2);
    }
    return 0;
}
