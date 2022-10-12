#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <pthread.h>

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
                getcwd(path, 1000);
                printf("%s\n", path);
            } else if (strcmp("cd", tokenisedCommand[0]) == 0) {
                int status = chdir(tokenisedCommand[1]);
                if (status == -1) printError();
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
