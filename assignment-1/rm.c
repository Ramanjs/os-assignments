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
    if (unlink(path) == -1) {
        if (!(setOption2 && errno == ENOENT)) printf("%s", strerror(errno));
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
    char path[1000];

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
        getcwd(path, 1000);
        strcat(path, "/");
        strcat(path, files[i]);

        if (setOption1) removeIt(path, setOption2);
        else removeFile(path, setOption2);
    }
    return 0;
}
