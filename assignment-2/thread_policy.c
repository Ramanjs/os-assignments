#include <bits/time.h>
#include <bits/types/struct_sched_param.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>

static struct timespec get_time_diff(struct timespec start, struct timespec finish) {
    struct timespec time_diff;
    time_diff.tv_sec = finish.tv_sec - start.tv_sec;
    time_diff.tv_nsec = finish.tv_nsec - start.tv_nsec;

    if (time_diff.tv_nsec < 0) {
        time_diff.tv_nsec += 1000000000;
        time_diff.tv_sec -= 1;
    }

    return time_diff;
}

/*static void*/
/*display_sched_attr(int policy, struct sched_param *param)*/
/*{*/
   /*printf("    policy=%s, priority=%d\n",*/
           /*(policy == SCHED_FIFO)  ? "SCHED_FIFO" :*/
           /*(policy == SCHED_RR)    ? "SCHED_RR" :*/
           /*(policy == SCHED_OTHER) ? "SCHED_OTHER" :*/
           /*"???",*/
           /*param->sched_priority);*/
/*}*/

/*static void*/
/*display_thread_sched_attr(FILE* fd, char *msg)*/
/*{*/
   /*int policy, s;*/
   /*struct sched_param param;*/

   /*s = pthread_getschedparam(pthread_self(), &policy, &param);*/

   /*fprintf(fd, "%s\n", msg);*/
   /*display_sched_attr(policy, &param);*/
/*}*/

void count_A() {
    long long int limit = (long long int) pow((double) 2, (double) 32);
    long long int i = 1;
    while (i <= limit) {
        i++;
    }
}

void count_B() {
    long long int limit = (long long int) pow((double) 2, (double) 32);
    long long int i = 1;
    while (i <= limit) {
        i++;
    }
}

void count_C() {
    long long int limit = (long long int) pow((double) 2, (double) 32);
    long long int i = 1;
    while (i <= limit) {
        i++;
    }
}

void* thr_A(void* args) {
    struct timespec start, finish, time_diff;

    clock_gettime(CLOCK_REALTIME, &start);
    count_A();
    clock_gettime(CLOCK_REALTIME, &finish);

    time_diff = get_time_diff(start, finish);

    /*printf("Ran thread A\n");*/
    /*display_thread_sched_attr("Scheduler attributes of new thread");*/

    FILE* fd = fopen("thread-a", "a");
    fprintf(fd, "%d.%.9lds\n", (int)time_diff.tv_sec, time_diff.tv_nsec);
    fclose(fd);

    return NULL;
}

void* thr_B(void* args) {
    struct timespec start, finish, time_diff;

    clock_gettime(CLOCK_REALTIME, &start);
    count_B();
    clock_gettime(CLOCK_REALTIME, &finish);

    time_diff = get_time_diff(start, finish);

    /*printf("Ran thread B\n");*/
    /*display_thread_sched_attr("Scheduler attributes of new thread");*/
    FILE* fd = fopen("thread-b", "a");
    fprintf(fd, "%d.%.9lds\n", (int)time_diff.tv_sec, time_diff.tv_nsec);
    fclose(fd);

    return NULL;
}

void* thr_C(void* args) {
    struct timespec start, finish, time_diff;

    clock_gettime(CLOCK_REALTIME, &start);
    count_C();
    clock_gettime(CLOCK_REALTIME, &finish);

    time_diff = get_time_diff(start, finish);

    /*printf("Ran thread C\n");*/
    /*display_thread_sched_attr("Scheduler attributes of new thread");*/
    FILE* fd = fopen("thread-c", "a");
    fprintf(fd, "%d.%.9lds\n", (int)time_diff.tv_sec, time_diff.tv_nsec);
    fclose(fd);

    return NULL;
}

void get_thread_time(pthread_t* thread, pthread_attr_t* attr, void* (*worker)(void *), struct sched_param* param, int policy, int priority) {
    int status;

    status = pthread_attr_init(attr);
    if (status != 0) {
        printf("%s\n", strerror(status));
        return;
    }

    status = pthread_attr_setinheritsched(attr, PTHREAD_EXPLICIT_SCHED);
    if (status != 0) {
        printf("%s\n", strerror(status));
    }

    status = pthread_attr_setschedpolicy(attr, policy);
    if (status != 0) {
        printf("%s\n", strerror(status));
    }

    param->sched_priority = priority;
    status = pthread_attr_setschedparam(attr, param);
    if (status != 0) {
        printf("%s\n", strerror(status));
    }


    status = pthread_create(thread, attr, worker, NULL);
    if (status != 0) {
        printf("%s\n", strerror(status));
    }
}

int main() {
    int status;

    pthread_t thread_A;
    pthread_attr_t attr_A;
    pthread_t thread_B;
    pthread_attr_t attr_B;
    pthread_t thread_C;
    pthread_attr_t attr_C;

    struct sched_param param;

    for (int i = 0; i < 5; i++) {
        get_thread_time(&thread_A, &attr_A, &thr_A, &param, SCHED_OTHER, 0);
        get_thread_time(&thread_B, &attr_B, &thr_B, &param, SCHED_RR, 1 + 5 * i);
        get_thread_time(&thread_C, &attr_C, &thr_C, &param, SCHED_FIFO, 1 + 10 * i);

        pthread_join(thread_A, NULL);
        pthread_join(thread_B, NULL);
        pthread_join(thread_C, NULL);
    }

    for (int i = 0; i < 5; i++) {
        get_thread_time(&thread_A, &attr_A, &thr_A, &param, SCHED_OTHER, 0);
        get_thread_time(&thread_B, &attr_B, &thr_B, &param, SCHED_RR, 2 + 10 * i);
        get_thread_time(&thread_C, &attr_C, &thr_C, &param, SCHED_FIFO, 2 + 5 * i);

        pthread_join(thread_A, NULL);
        pthread_join(thread_B, NULL);
        pthread_join(thread_C, NULL);
    }    

    return 0;
}
