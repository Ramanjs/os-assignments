const int dateTimeLength = 100;

char** tokeniseString(char* string, int *args, char token); // split string using specified delimiter

char **getFilesArray(); // malloc memory for files array

void extractArguments(char **files, char *argv[], int argc, char option1, char option2, int *setOption1, int *setOption2, int *numFiles); // extract arguments from argv

int isDir(char *path); // check if path is a directory

int isLink(char *path); // check if path is a symlink

int isFile(char *path); // check if path is a regular file
