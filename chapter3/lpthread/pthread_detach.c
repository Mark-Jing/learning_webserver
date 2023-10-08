#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void* callback(void*) {
    printf("child thread id : %ld\n", pthread_self());
    return 0;
}

int main() {
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, callback, NULL);
    if(ret != 0) {
        char *errstr = strerror(ret);
        printf("pthread error: %s\n", errstr);
    }
    printf("tid: %ld, main thread: %ld\n", tid, pthread_self());
    pthread_detach(tid);
    int err = pthread_join(tid, NULL);
    if(err != 0) {
        char *errstr = strerror(err);
        printf("pthread_join error : %s\n", errstr);
    }
    pthread_exit(NULL);
    return 0;
}