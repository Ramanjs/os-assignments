#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

void write_result_to_file(char name, struct timespec time_diff) {
    char file_name[] = "result-";
    strncat(file_name, &name, 1);
    FILE* fd = fopen(file_name, "a");
    fprintf(fd, "%d.%.9lds\n", (int)time_diff.tv_sec, time_diff.tv_nsec);
    fclose(fd);
}

int get_sched_policy(char name) {
    if (name == 'a') return SCHED_OTHER;
    if (name == 'b') return SCHED_RR;
    if (name == 'c') return SCHED_FIFO;
}

struct timespec get_time_diff(struct timespec start, struct timespec finish) {
    struct timespec time_diff;
    time_diff.tv_sec = finish.tv_sec - start.tv_sec;
    time_diff.tv_nsec = finish.tv_nsec - start.tv_nsec;

    if (time_diff.tv_nsec < 0) {
        time_diff.tv_nsec += 1000000000;
        time_diff.tv_sec -= 1;
    }

    return time_diff;
}

void process(char name, int priority) {
    struct timespec start, finish, time_diff;

    clock_gettime(CLOCK_REALTIME, &start);

    struct sched_param param;
    param.sched_priority = priority;
    int policy = get_sched_policy(name);
    pthread_setschedparam(pthread_self(), policy, &param);

    int child = fork();
    if (child == 0) {
        // exec()
        char path_name[] = "compile-script-";
        strncat(path_name, &name, 1);
        strcat(path_name, ".sh");
        execl(path_name, (char *) NULL);
    } else {
        wait(NULL);
        clock_gettime(CLOCK_REALTIME, &finish);
        time_diff = get_time_diff(start, finish);
        write_result_to_file(name, time_diff);
   }
}

int main() {
    printf("Starting the forking process");

    int child_one = fork();
    if (child_one < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    if (child_one == 0) {
        process('a', 0);
    } else {
        int child_two = fork();
        if (child_two == 0) {
            process('b', 1);
        } else {
            int child_three = fork();
            if (child_three == 0) {
                process('c', 2);
            } else {
                int wstatus;
                wstatus = waitpid(child_one, &wstatus, 0);
                wstatus = waitpid(child_two, &wstatus, 0);
                wstatus = waitpid(child_three, &wstatus, 0);
            }
        }
    }
    return 0;
}
