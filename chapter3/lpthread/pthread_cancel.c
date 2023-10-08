#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void* callback(void*) {
    printf("child thread id : %ld\n", pthread_self());
    for(int i = 0; i < 10; i++) {
        printf("child: %d\n", i);
        if(i == 3) {
            sleep(0.5);
        }
    }
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

    pthread_cancel(pthread_self());

    for(int i = 0; i < 5; i++) {
        printf("%d\n", i);
    }

    pthread_exit(NULL);
    return 0;
}