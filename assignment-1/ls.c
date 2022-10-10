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

char* getPermissionsString(struct stat *attrib){
    char *permissions = malloc(10 * sizeof(char));
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
    char **files = malloc(10 * sizeof(char*));
    for (int i = 0; i < 10; ++i) {
        files[i] = malloc(100 * sizeof(char));
        files[i][0] = '\0';
    }
    int numFiles = 0;

    // Extract arguments and options
    if (argc == 1) {
        files[0] = getcwd(files[0], 1000);
        numFiles = 1;
    } else {
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
    }

    if (numFiles == 0) {
        files[0] = getcwd(files[0], 1000);
        numFiles = 1;
    }

    for (int i = 0; i < numFiles; i++) {
        DIR *dir = opendir(files[i]);
        struct dirent *currentEntry = readdir(dir);

        if (numFiles > 1) printf("%s:\n", files[i]);

        if (setOption1) {
            while (currentEntry != NULL) {
                struct stat attrib;
                char filePath[100];
                filePath[0] = '\0';
                strcat(filePath, files[i]);
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
