#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void * callback(void * arg) {
    printf("thread id : %ld\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t tid;

    // 创建一个子线程
    int ret = pthread_create(&tid, NULL, callback, NULL);

    if(ret != 0) {
        char * errstr = strerror(ret);
        printf("error : %s\n", errstr);
    } 

    for(int i = 0; i < 5; i++) {
        printf("%d\n", i);
    }

    pthread_exit(NULL);

    return 0;   // exit(0);
}