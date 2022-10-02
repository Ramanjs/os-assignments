#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

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

char** tokeniseString(char* string, int *args) {
    char** tokenisedString = malloc(5 * sizeof(char*));
    for (int i = 0; i < 5; ++i) {
        tokenisedString[i] = malloc(100 * sizeof(char*));
        tokenisedString[i][0] = '\0';
    }
    int index = 0;
    for (int i = 0; i < strlen(string); ++i) {
        if (string[i] != ' ') {
            strncat(tokenisedString[index], &string[i], 1);
        } else {
            index++;
            (*args)++;
        }
    }
    tokenisedString[index + 1] = (char *)NULL;
    return tokenisedString;
}

int isExternalCommand(char *command) {
    int result = 0;
    if (strcmp(command, "ls") == 0) result = 1;
    if (strcmp(command, "cat") == 0) result = 1;
    if (strcmp(command, "date") == 0) result = 1;
    if (strcmp(command, "rm") == 0) result = 1;
    if (strcmp(command, "mkdir") == 0) result = 1;
    return result;
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
            char **tokenisedCommand = tokeniseString(command, &args);
            if (strcmp("pwd", tokenisedCommand[0]) == 0) {
                getcwd(path, 1000);
                printf("%s\n", path);
            } else if (strcmp("cd", tokenisedCommand[0]) == 0) {
                int status = chdir(tokenisedCommand[1]);
                if (status == -1) {
                    if (errno == 1) {
                        printf("Permission denied\n");
                    } else if (errno == 2) {
                        printf("No such file or directory\n");
                    }
                }
            } else if (strcmp("echo", tokenisedCommand[0]) == 0) {
                for (int i = 1; i <= args; i++) {
                    printf("%s ", tokenisedCommand[i]);
                }
                printf("\n");
            } else if (strcmp("exit", tokenisedCommand[0]) == 0) {
                printf("Thanks for visiting, cya.\n");
                break;
            } else if (isExternalCommand(tokenisedCommand[0])) {
                int rc = fork();
                getcwd(path, 1000);
                strcat(path, "/");
                if (rc == 0) {
                    char err[100];
                    if (execv(strcat(path, tokenisedCommand[0]), &tokenisedCommand[0]) == -1) {
                        perror(err);
                        printf("%s", err);
                    }
                } else {
                    int wstatus;
                    waitpid(rc, &wstatus, 0);
                }
            } else {
                printf("bash: %s: command not found\n", tokenisedCommand[0]);
            }
            for (int i = 0; i < args; ++i) {
                free(tokenisedCommand[i]);
            }
            free(tokenisedCommand);
        }
        free(command);
    }
    return 0;
}
