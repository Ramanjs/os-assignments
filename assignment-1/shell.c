#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <pthread.h>
#include <limits.h>

#include "utils.h"

char* takeInput() {
    char* command = malloc(1000 * sizeof(char));
    int index = 0;
    char ch = fgetc(stdin);
    while (ch != '\n') {
        command[index] = ch;
        index++;
        ch = fgetc(stdin);
    }
    command[index] = '\0';
    return command;
}

int isExternalCommand(char *command) {
    int result = 0;
    if (strcmp(command, "myls") == 0) result = 1;
    if (strcmp(command, "mycat") == 0) result = 1;
    if (strcmp(command, "mydate") == 0) result = 1;
    if (strcmp(command, "myrm") == 0) result = 1;
    if (strcmp(command, "mymkdir") == 0) result = 1;
    return result;
}

void *worker(void *arg) {
    char *command = arg;
    system(command);
    return NULL;
}

void printError() {
    char err[100];
    perror(err);
    printf("%s", err);
}

void echo(char **tokenisedCommand, int args) {
    char option1 = 'n';
    char option2 = 'e';
    int setOption1 = 0;
    int setOption2 = 0;

    char **strings = getFilesArray();
    int numStrings = 0;

    extractArguments(strings, tokenisedCommand, args, option1, option2, &setOption1, &setOption2, &numStrings);

    for (int i = 0; i < numStrings; ++i) {
        printf("%s ", strings[i]);
    }
    if (!setOption1) printf("\n");
}

void cd(char **tokenisedCommand, int args) {
    char option1 = 'L';
    char option2 = 'P';
    int setOption1 = 1;
    int setOption2 = 0;

    // Define files array
    char **files = getFilesArray();
    int numFiles = 0;

    extractArguments(files, tokenisedCommand, args, option1, option2, &setOption1, &setOption2, &numFiles);

    if (numFiles > 1) {
        printf("Too many arguments\n");
        return;
    }

    char* cwd;
    cwd = getenv("PWD");

    if (strcmp(files[0], "../") == 0 || strcmp(files[0], "..") == 0) {
        if (strlen(cwd) == 0) {
            return;
        }

        int lastSlashIndex = strlen(cwd) - 1;
        while (cwd[lastSlashIndex] != '/') {
            lastSlashIndex--;
        }
        char substr[100];
        memcpy(substr, &cwd[0], lastSlashIndex);
        substr[lastSlashIndex] = '\0';
        setenv("PWD", substr, 1);
        return;
    }

    char newPath[1000];
    strcpy(newPath, cwd);
    strcat(newPath, "/");
    strcat(newPath, files[0]);

    if (setOption2 || !isLink(newPath)) {
        char *temp;
        temp = realpath(newPath, NULL);
        if (temp == NULL) {
            printf("No such file or directory\n");
            return;
        }
        strcpy(newPath, temp);
    }
    setenv("PWD", newPath, 1);
}

void pwd(char **tokenisedCommand, int args) {
    char option1 = 'L';
    char option2 = 'P';
    int setOption1 = 1;
    int setOption2 = 0;

    // Define files array
    char **files = getFilesArray();
    int numFiles = 0;

    extractArguments(files, tokenisedCommand, args, option1, option2, &setOption1, &setOption2, &numFiles);

    if (numFiles > 0) {
        printf("Too many arguments\n");
        return;
    }

    char* cwd;
    cwd = getenv("PWD");

    if (setOption2) {
        cwd = realpath(cwd, NULL);
    }
    printf("%s\n", cwd);
}

int main() {
    printf("Welcome to my shell!\n");
    char *path = malloc(1000 * sizeof(char));
    char* command;
    while (1) {
        printf("$ ");
        command = takeInput();
        if (strlen(command) > 0) {
            int args = 0;
            char **tokenisedCommand = tokeniseString(command, &args, ' ');
            if (strcmp("pwd", tokenisedCommand[0]) == 0) {
                pwd(tokenisedCommand, args);
            } else if (strcmp("cd", tokenisedCommand[0]) == 0) {
                cd(tokenisedCommand, args);
            } else if (strcmp("echo", tokenisedCommand[0]) == 0) {
                echo(tokenisedCommand, args);
            } else if (isExternalCommand(tokenisedCommand[0])) {
                if (strcmp(tokenisedCommand[args - 1], "&t") == 0) {
                    char *externalCommand = malloc(1000 * sizeof(char));
                    externalCommand[0] = '\0';
                    for (int i = 0; i < args - 1; ++i) {
                        strcat(externalCommand, tokenisedCommand[i]);
                        strcat(externalCommand, " ");
                    }
                    pthread_t newThread;
                    pthread_create(&newThread, NULL, &worker, externalCommand);
                    pthread_join(newThread, NULL);
                } else {
                    int rc = fork();
                    getcwd(path, 1000);
                    strcat(path, "/");
                    if (rc == 0) {
                        if (execv(strcat(path, tokenisedCommand[0]), &tokenisedCommand[0]) == -1) printError();
                        return 0;
                    } else {
                        int wstatus;
                        waitpid(rc, &wstatus, 0);
                    }
                }
            } else if (strcmp("exit", tokenisedCommand[0]) == 0) {
                printf("Thanks for visiting, cya.\n");
                break;
            } else {
                printf("bash: %s: command not found\n", tokenisedCommand[0]);
            }
        }
        free(command);
    }
    return 0;
}
