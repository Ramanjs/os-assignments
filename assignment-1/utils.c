#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char **getFilesArray() {
    char **files = malloc(10 * sizeof(char*));
    for (int i = 0; i < 10; ++i) {
        files[i] = malloc(100 * sizeof(char));
        files[i][0] = '\0';
    }
    return files;
}

void extractArguments(char **files, char *argv[], int argc, char option1, char option2, int *setOption1, int *setOption2, int *numFiles) {
    // Extract arguments and options
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 0; j < strlen(argv[i]); j++) {
                if (argv[i][j] == option1) *setOption1 = 1;
                if (argv[i][j] == option2) *setOption2 = 1;
            }
        } else {
            strcat(files[*numFiles], argv[i]);
            (*numFiles)++;
        }
    }
}

int isDir(char *path) {
    struct stat attrib;
    stat(path, &attrib);
    return S_ISDIR(attrib.st_mode);
}
