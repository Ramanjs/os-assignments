#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#include "utils.h"

char* getPermissionsString(struct stat *attrib){
    char permissions[10];
    mode_t perm = attrib->st_mode;
    permissions[0] = (perm & S_IRUSR) ? 'r' : '-';
    permissions[1] = (perm & S_IWUSR) ? 'w' : '-';
    permissions[2] = (perm & S_IXUSR) ? 'x' : '-';
    permissions[3] = (perm & S_IRGRP) ? 'r' : '-';
    permissions[4] = (perm & S_IWGRP) ? 'w' : '-';
    permissions[5] = (perm & S_IXGRP) ? 'x' : '-';
    permissions[6] = (perm & S_IROTH) ? 'r' : '-';
    permissions[7] = (perm & S_IWOTH) ? 'w' : '-';
    permissions[8] = (perm & S_IXOTH) ? 'x' : '-';
    permissions[9] = '\0';
    return permissions;
}

int main(int argc, char *argv[]) {
    // Defile options
    char option1 = 'l';
    char option2 = 'a';
    int setOption1 = 0;
    int setOption2 = 0;

    // Define files array
    char **files = getFilesArray();
    int numFiles = 0;

    // Extract arguments and options
    extractArguments(files, argv, argc, option1, option2, &setOption1, &setOption2, &numFiles);

    if (numFiles == 0) {
        files[0] = getenv("PWD");
        numFiles = 1;
    }

    for (int i = 0; i < numFiles; i++) {

        if (!isDir(files[i])) {
            if (setOption1) {
                struct stat attrib;
                if (stat(files[i], &attrib) != 0) {
                    printf("%s\n", strerror(errno));
                } else {
                    char *permissions = getPermissionsString(&attrib);
                    int nlinks = attrib.st_nlink;

                    int uid = attrib.st_uid;
                    struct passwd *usr = getpwuid(uid);

                    int gid = attrib.st_gid;
                    struct group *grp = getgrgid(gid);

                    int size = attrib.st_size;
                    char modifiedTime[100];
                    strftime(modifiedTime, sizeof(modifiedTime), "%b %e %H:%M", localtime(&(attrib.st_ctim)));
                    printf("%s %d %s %s %10d %s %s\n", permissions, nlinks, usr->pw_name, grp->gr_name, size, modifiedTime, files[i]);
                    free(permissions);
                }
            } else {
                printf("%s\n", files[i]);
            }
            continue;
        }

        DIR *dir = opendir(files[i]);
        struct dirent *currentEntry = readdir(dir);

        if (numFiles > 1) printf("%s:\n", files[i]);

        if (setOption1) {
            while (currentEntry != NULL) {
                struct stat attrib;
                char filePath[100];
                strcpy(filePath, files[i]);
                strcat(filePath, "/");
                strcat(filePath, currentEntry->d_name);
                if (stat(filePath, &attrib) != 0) {
                    printf("%s\n", strerror(errno));
                } else {
                    if (!setOption2 && currentEntry->d_name[0] == '.') {
                        currentEntry = readdir(dir);
                        continue;
                    }

                    char *permissions = getPermissionsString(&attrib);
                    int nlinks = attrib.st_nlink;

                    int uid = attrib.st_uid;
                    struct passwd *usr = getpwuid(uid);

                    int gid = attrib.st_gid;
                    struct group *grp = getgrgid(gid);

                    int size = attrib.st_size;
                    char modifiedTime[100];
                    strftime(modifiedTime, sizeof(modifiedTime), "%b %e %H:%M", localtime(&(attrib.st_ctim)));
                    printf("%s %d %s %s %10d %s %s\n", permissions, nlinks, usr->pw_name, grp->gr_name, size, modifiedTime, currentEntry->d_name);

                    free(permissions);
                }

                currentEntry = readdir(dir);
            }
        } else {
            while (currentEntry != NULL) {
                if (!setOption2 && currentEntry->d_name[0] == '.') {
                    currentEntry = readdir(dir);
                    continue;
                }
                printf("%s  ", currentEntry->d_name);
                currentEntry = readdir(dir);
            }
        }
        printf("\n");
    }
    return 0;
}
